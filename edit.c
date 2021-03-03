/**
 * Interfaccia privata dalla libreria edit.h
 *
 * @author      Giorgio Paoletti
 *              giorgio.paoletti@studenti.unicam.it
 *              matricola: 105056
 *
 * @version     Seconda Consegna 25/09/2020
 *
 */
#include <stdlib.h>
#include <string.h>
#include "edit.h"
#include "list.h"
#include "edit_instruction.h"

int minimum(int, int, int);
long int write_instruction(edit_instruction_t**, FILE*, long int);
int apply_instruction(edit_instruction_t*, FILE*, int*);

/**
 * Struct che permette la memorizzazione della Matrice di Edit legata a 2 file
 * La struct e composta da una matrice che rappresenta la matrice di Edit,
 * e 2 puntatori che contengono i byte contenuti nei 2 file da cui e stata ricavata la matrice di Edit
 */
typedef struct edit_matrix_t{
    int** matrix;
    byte_list_t* f1_content_list;
    byte_list_t* f2_content_list;
} edit_matrix_t;

/**
 * Alloca la struct prendendo come parametri i 2 path collgati ai 2 file
 * La matrice viene generata utilizzando l'algoritmo Wagner–Fischer
 *
 * @return puntatore alla struct
 */
edit_matrix_t* matrix_create (char* in1, char* in2){

    edit_matrix_t* editMatrix = malloc(sizeof(edit_matrix_t));

    editMatrix->f1_content_list = list_create(in1);
    editMatrix->f2_content_list = list_create(in2);

    int m = list_get_size(editMatrix->f1_content_list);
    int n = list_get_size(editMatrix->f2_content_list);

    editMatrix->matrix = (int**) malloc((m + 1) * sizeof(int*));
    for(int i = 0; i <= m; i++)
        editMatrix->matrix[i] = (int*) malloc((n + 1) * sizeof(int));

    for(int i=0; i<=m; i++) for(int j=0; j<=n; j++) editMatrix->matrix[i][j] = 0;
    for(int i=1; i<=m; i++) editMatrix->matrix[i][0] = i;
    for(int j=1; j<=n; j++) editMatrix->matrix[0][j] = j;
    for(int j=1; j<=n; j++)
        for(int i=1; i<=m; i++){
            int substitutionCost = list_get_element(editMatrix->f1_content_list, i-1) == list_get_element(editMatrix->f2_content_list, j-1) ? 0 : 1;
            editMatrix->matrix[i][j] = minimum(editMatrix->matrix[i-1][j] + 1,editMatrix->matrix[i][j-1] + 1,editMatrix->matrix[i-1][j-1] + substitutionCost);
        }
    return editMatrix;
}

int minimum(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

/**
 * Dealloca la struct passata per argomento
 */
void matrix_destroy(edit_matrix_t** editMatrix){
    for(int i = 0; i <= list_get_size((*editMatrix)->f1_content_list); i++)
        free((*editMatrix)->matrix[i]);
    free((*editMatrix)->matrix);
    list_destroy(&(*editMatrix)->f1_content_list);
    list_destroy(&(*editMatrix)->f2_content_list);
    free(*editMatrix);
}

/**
 * Restituisce la distanza di Edit legata ai 2 file a cui
 * appartiene la matrice passata per argomento
 * @return Distanza di Edit
 */
int get_edit_distance (edit_matrix_t* editMatrix){
    return editMatrix->matrix[list_get_size(editMatrix->f1_content_list)][list_get_size(editMatrix->f2_content_list)];
}

/**
 * Memorizza sul file il cui path e stato passato per argomento le istruzioni
 * estrapolate dalla matrice di Edit legata alla matrice passat per argomento
 */
void generate_instructions_file(edit_matrix_t* editMatrix, char* out){

    FILE* fout = fopen(out, "wb");
    if(fout == NULL) perror("Errore: ");

    long int current_pos = 0L;

    int i = list_get_size(editMatrix->f1_content_list);
    int j = list_get_size(editMatrix->f2_content_list);

    while(i>=0 || j>=0) {
        if((editMatrix->matrix[i-1][j-1] <= editMatrix->matrix[i-1][j] && editMatrix->matrix[i-1][j-1] <= editMatrix->matrix[i][j-1] ) &&
           (editMatrix->matrix[i-1][j-1]  == editMatrix->matrix[i][j] || editMatrix->matrix[i-1][j-1] + 1 == editMatrix->matrix[i][j])){
            if(editMatrix->matrix[i-1][j-1] + 1 == editMatrix->matrix[i][j]) {
                edit_instruction_t *instr = instruction_create((unsigned char *) "SET", i, list_get_element(editMatrix->f2_content_list, j-1));
                current_pos = write_instruction(&instr, fout, current_pos);
            }
            i--;
            j--;
        } else if( (editMatrix->matrix[i][j-1] <= editMatrix->matrix[i-1][j]) &&
                   (editMatrix->matrix[i][j-1] == editMatrix->matrix[i][j] || editMatrix->matrix[i][j-1] + 1  == editMatrix->matrix[i][j])){
            edit_instruction_t *instr = instruction_create((unsigned char *) "ADD", i, list_get_element(editMatrix->f2_content_list, j-1));
            current_pos = write_instruction(&instr, fout, current_pos);
            j--;
        } else {
            edit_instruction_t *instr = instruction_create((unsigned char *) "DEL", i, 0);
            current_pos = write_instruction(&instr, fout, current_pos);
            i--;
        }
        fflush(fout);
    }
    fclose(fout);
}

/**
 * Si occupa di scrivere la singola istruzione sul file il cui path e
 * passato come secondo parametro alla posizione passata come terzo parametro
 */
long int write_instruction(edit_instruction_t** instr, FILE* fout, long int current_pos){
    fseek(fout, current_pos,SEEK_SET);
    fwrite(get_instruction_name(*instr), sizeof(unsigned char)*3, 1, fout);
    unsigned int pos = get_instruction_pos(*instr);
    fwrite(&pos, sizeof(unsigned int), 1, fout);
    putc(get_instruction_byte(*instr), fout);
    instruction_destroy(instr);
    return ftell(fout);
}

/**
 * Applica le istruzioni contenute nel file il cui path e stato passato come secondo
 * argomento al file il cui path e stato passato come primo argomento
 * Il risultato viene memorizzato nel file il cui path e stato passato come terzo argomento
 */
void apply_instructions_file(char* in, char* instr, char* out){
    FILE* fin = fopen(in, "rb");
    if(fin == NULL) perror("Errore: ");
    FILE* finstr = fopen(instr, "rb");
    if(finstr == NULL) perror("Errore: ");
    FILE* fout = fopen(out, "wb");
    if(fout == NULL) perror("Errore: ");

    byte_list_t* list_fin = list_create(in);

    unsigned long size = 0;
    int curr_pos = list_get_size(list_fin);
    do{
        unsigned char buffer[3];
        size += fread(buffer, sizeof(unsigned char), 3, finstr);
        unsigned int* pos = malloc(sizeof(unsigned int));
        size += fread(pos, sizeof(unsigned int), 1, finstr);
        unsigned char* byt = malloc(sizeof(unsigned char));
        size += fread(byt, sizeof(unsigned char), 1, finstr);
        if(size != 0){
            edit_instruction_t* instruction = instruction_create(buffer, *pos, *byt);
            while(get_instruction_pos(instruction) < curr_pos){
                fputc(list_get_element(list_fin, curr_pos-1), fout);
                curr_pos--;
            }
            if(apply_instruction(instruction, fout, &curr_pos) == -1) break;
            instruction_destroy(&instruction);
            size = 0;
        } else {
            while (curr_pos > 0){
                fputc(list_get_element(list_fin, curr_pos-1), fout);
                curr_pos--;
            }
        }
        if(pos) free(pos);
        if(byt) free(byt);
    }while (curr_pos > 0);
    fflush(fout);
    list_destroy(&list_fin);

    byte_list_t* list_fout = list_create(out);
    rewind(fout);
    for(int i=list_get_size(list_fout)-1; i>=0 ; i--) fputc(list_get_element(list_fout, i), fout);
    list_destroy(&list_fout);

    fclose(fin);
    fclose(finstr);
    fclose(fout);
}

/**
 * Si occupa di applicare la singola istruzione a secondo del tipo (SET|DEL|ADD)
 */
int apply_instruction(edit_instruction_t* instr, FILE* fout, int* curr_pos){
    if(memcmp(get_instruction_name(instr), (unsigned char*) "SET", sizeof(unsigned char)*3) == 0){
        fputc(get_instruction_byte(instr), fout);
        (*curr_pos)--;
        return 0;
    } else if(memcmp(get_instruction_name(instr), (unsigned char*) "ADD", sizeof(unsigned char)*3) == 0){
        fputc(get_instruction_byte(instr), fout);
        return 0;
    } else if(memcmp(get_instruction_name(instr), (unsigned char*) "DEL", sizeof(unsigned char)*3) == 0){
        (*curr_pos)--;
        return 0;
    } else{
        perror("Some wrong with given data");
        return -1;
    }
}






