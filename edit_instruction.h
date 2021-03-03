/**
 * La libreria mette a disposizione una struttura dati che consente la memorizzazione di un istruzione ricavata dalla matrice di Edit
 *
 * @author      Giorgio Paoletti
 *              giorgio.paoletti@studenti.unicam.it
 *              matricola: 105056
 *
 * @version     Seconda Consegna 25/09/2020
 *
 */
#ifndef GIORGIOPAOLETTI105056_EDIT_INSTRUCTION_H
#define GIORGIOPAOLETTI105056_EDIT_INSTRUCTION_H

#include "edit.h"

/**
 * Struct che permette la memorizzazione di un istruzione ricavata dalla matrice di Edit
 */
typedef struct edit_instruction_t edit_instruction_t;

/**
 * Alloca la struct prendendo i byte dal file passato per argomento
 *
 * @param   Tipo istruzione (SET|ADD|DEL)
 * @param   Posizione da modificare
 * @param   Byte da utilizzare
 * @return  puntatore alla struct
 */
edit_instruction_t* instruction_create(unsigned char*, unsigned int, unsigned char);

/**
 * Dealloca la struct passata per argomento
 * @param   puntatore alla struct da deallocare
 */
void instruction_destroy(edit_instruction_t**);

unsigned int get_instruction_pos(edit_instruction_t*);

unsigned char get_instruction_byte(edit_instruction_t*);

unsigned char* get_instruction_name(edit_instruction_t*);

#endif //GIORGIOPAOLETTI105056_EDIT_INSTRUCTION_H
