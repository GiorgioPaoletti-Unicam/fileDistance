/**
 * Interfaccia privata dalla libreria list.h
 *
 * @author      Giorgio Paoletti
 *              giorgio.paoletti@studenti.unicam.it
 *              matricola: 105056
 *
 * @version     Seconda Consegna 25/09/2020
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void add_node(unsigned char*, byte_list_t **, byte_list_t **, int);
byte_list_t* create_node(unsigned char*, int);

/**
 * Struct che permette la memorizzazione dei byte di un file senza conoscerne la lunghezza
 * La struct corrisponde a un nodo composto da un blocco di byte (massimo 256), un size del blocco e il puntatore al nodo successivo
 */
typedef struct byte_list_t {
    unsigned char *byte_block;
    byte_list_t *next;
    int size;
} byte_list_t;

/**
 * Alloca la struct prendendo i byte dal file passato per argomento
 * Il file viene aperto tramite il flag 'rb' che permette la lettura in formato binario
 * vengono letti blocchi di 256 byte alla volta e ne viene costruito il nodo corrispondente
 * che poi viene collocato nella lista
 *
 * @param in    path del file da cui prendere i byte
 * @return      puntatore alla struct
 */
byte_list_t* list_create(char* in){

    byte_list_t *first = NULL;
    byte_list_t *last = NULL;

    FILE* fin = fopen(in, "rb");
    if(fin == NULL) perror("Errore: ");
    unsigned char buffer[256];

    int size=0;
    do{
        size = fread(buffer, sizeof(unsigned char), 256, fin);
        if(size != 0) add_node(buffer, &first, &last, size);
    }while(size != 0);

    fclose(fin);
    return first;
}

/**
 * Aggiunge un nodo alla lista
 */
void add_node(unsigned char* content, byte_list_t **first, byte_list_t **last, int size){
    byte_list_t *new_node = create_node(content, size);

    if(*first == NULL){
        *first = new_node;
    } else {
        (*last)->next = new_node;
    }
    *last = new_node;
}

/**
 * Crea un nodo dato il blocco di byte e la corrispondente size
 */
byte_list_t* create_node(unsigned char* block_content, int size){
    byte_list_t *new_node = malloc(sizeof(struct byte_list_t));

    new_node->byte_block = malloc(sizeof(unsigned char) * size);
    for(int i=0; i<= size; i++){
        new_node->byte_block[i] = block_content[i];
    }

    new_node->size = size;
    new_node->next = NULL;
    return new_node;
}

/**
 * Dealloca la struct passata per argomento
 * @param list  puntatore alla struct da deallocare
 */
void list_destroy(byte_list_t **list){
    while((*list)->next){
        free((*list)->byte_block);
        *list = (*list)->next;
    }
    free((*list)->byte_block);
    free(*list);
}

/**
 * Restituisce il numero di byte che compongono il file
 * @param list  lista da cui ricavare la size
 * @return      il numero di byte che compongono il file
 */
int list_get_size(byte_list_t *list){
    int size = 0;
    while(list->next){
        size+= list->size;
        list = list->next;
    }
    size+= list->size;
    return size;
}

/**
 * Restituisce il byte corrispondente all'indice passato per argomento
 * @param list  lista da cui estrarre il byte
 * @param index indice del byte desiderato
 * @return      byte corrispondente all'indice
 */
unsigned char list_get_element(byte_list_t *list, int index){
    if(list_get_size(list) < index) perror("Errore: index not exist");
    int i =0;
    if(list_get_size(list) > 256)
        while (i+256 <= index){
            i+=256;
            list = list->next;
        }
    return list->byte_block[index-i];
}

