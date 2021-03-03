/**
 * Interfaccia privata dalla libreria edit_instruction.h
 *
 * @author      Giorgio Paoletti
 *              giorgio.paoletti@studenti.unicam.it
 *              matricola: 105056
 *
 * @version     Seconda Consegna 25/09/2020
 *
 */

#include <stdlib.h>
#include "edit_instruction.h"

/**
 * Struct che permette la memorizzazione di un istruzione ricavata dalla matrice di Edit
 */
typedef struct edit_instruction_t{
    unsigned char *instruction;
    unsigned int pos;
    unsigned char byte;
}edit_instruction_t;

/**
 * Alloca la struct prendendo i byte dal file passato per argomento
 *
 * @param instruction   Tipo istruzione (SET|ADD|DEL)
 * @param pos           Posizione da modificare
 * @param byte          Byte da utilizzare
 * @return  puntatore alla struct
 */
edit_instruction_t* instruction_create(unsigned char* instruction, unsigned int pos, unsigned char byte){
    edit_instruction_t* instr = malloc(sizeof(struct edit_instruction_t*));
    instr->instruction = malloc(sizeof(unsigned char)*3);
    for(int i=0; i<=2; i++) instr->instruction[i] = instruction[i];
    instr->pos = pos;
    instr->byte = byte;
    return instr;
}

/**
 * Dealloca la struct passata per argomento
 * @param   puntatore alla struct da deallocare
 */
void instruction_destroy(edit_instruction_t** instr){
    free((*instr)->instruction);
    free(*instr);
}

unsigned int get_instruction_pos(edit_instruction_t* instr){
    return instr->pos;
}
unsigned char get_instruction_byte(edit_instruction_t* instr){
    return instr->byte;
}
unsigned char* get_instruction_name(edit_instruction_t* instr){
    return instr->instruction;
}