/**
 * La libreria mette a disposizione una struttura dati che consente la memorizzazione dei byte di un file senza conoscerne la lunghezza
 *
 * @author      Giorgio Paoletti
 *              giorgio.paoletti@studenti.unicam.it
 *              matricola: 105056
 *
 * @version     Seconda Consegna 25/09/2020
 *
 */
#ifndef GIORGIOPAOLETTI105056_LIST_H
#define GIORGIOPAOLETTI105056_LIST_H

/**
 * Struct che permette la memorizzazione dei byte di un file senza conoscerne la lunghezza
 */
typedef struct byte_list_t byte_list_t;

/**
 * Alloca la struct prendendo i byte dal file passato per argomento
 * @param in    path del file da cui prendere i byte
 * @return      puntatore alla struct
 */
byte_list_t *list_create(char* in);

/**
 * Dealloca la struct passata per argomento
 * @param list  puntatore alla struct da deallocare
 */
void list_destroy(byte_list_t **list);

/**
 * Restituisce il byte corrispondente all'indice passato per argomento
 * @param list  lista da cui estrarre il byte
 * @param index indice del byte desiderato
 * @return      byte corrispondente all'indice
 */
unsigned char list_get_element(byte_list_t *list, int index);

/**
 * Restituisce il numero di byte che compongono il file
 * @param list  lista da cui ricavare la size
 * @return      il numero di byte che compongono il file
 */
int list_get_size(byte_list_t *list);

#endif //GIORGIOPAOLETTI105056_LIST_H
