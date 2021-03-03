/**
 * La libreria mette a disposizione una struttura dati che consente la memorizzazione della Matrice di Edit legata a 2 file
 *
 * @author      Giorgio Paoletti
 *              giorgio.paoletti@studenti.unicam.it
 *              matricola: 105056
 *
 * @version     Seconda Consegna 25/09/2020
 *
 */
#ifndef GIORGIOPAOLETTI105056_EDIT_H
#define GIORGIOPAOLETTI105056_EDIT_H

#include <stdio.h>

/**
 * Struct che permette la memorizzazione della Matrice di Edit legata a 2 file
 */
typedef struct edit_matrix_t edit_matrix_t;

/**
 * Alloca la struct prendendo come parametri i 2 path collgati ai 2 file
 * @return puntatore alla struct
 */
edit_matrix_t* matrix_create (char*, char*);

/**
 * Dealloca la struct passata per argomento
 */
void matrix_destroy(edit_matrix_t **);

/**
 * Restituisce la distanza di Edit legata ai 2 file a cui
 * appartiene la matrice passata per argomento
 * @return Distanza di Edit
 */
int get_edit_distance (edit_matrix_t*);

/**
 * Memorizza sul file il cui path e stato passato per argomento le istruzioni
 * estrapolate dalla matrice di Edit legata alla matrice passat per argomento
 */
void generate_instructions_file(edit_matrix_t*, char*);

/**
 * Applica le istruzioni contenute nel file il cui path e stato passato come secondo
 * argomento al file il cui path e stato passato come primo argomento
 * Il risultato viene memorizzato nel file il cui path e stato passato come terzo argomento
 */
void apply_instructions_file(char*, char*, char*);

#endif //GIORGIOPAOLETTI105056_EDIT_H
