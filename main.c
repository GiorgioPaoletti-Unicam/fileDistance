/**
 * @author      Giorgio Paoletti
 *              giorgio.paoletti@studenti.unicam.it
 *              matricola: 105056
 *
 * @version     Seconda Consegna 25/09/2020
 *
 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "edit.h"

void printInfo() {
    printf("filedistance distance file1 file2\n"
           "filedistance distance file1 file2 output\n"
           "filedistance apply inputfile filem outputfile\n"
            /*"filedistance search inputfile dir\n"
            "filedistance searchall inputfile dir limit\n"*/);
}

int main(int argc, char **argv) {
    if (strcmp(argv[1], "distance")==0) {
        edit_matrix_t* editMatrix = matrix_create (argv[2], argv[3]);
        if(argc == 4){
            clock_t start = clock();
            printf("EDIT DISTANCE: %d\n", get_edit_distance(editMatrix));
            printf("TIME: %f\n", ((double)(clock() - start)) / CLOCKS_PER_SEC);
        }
        else if(argc == 5) generate_instructions_file(editMatrix, argv[4]);
        matrix_destroy(&editMatrix);
        return 0;
    }
    if (strcmp(argv[1], "apply")==0 && argc == 5) {
        apply_instructions_file(argv[2], argv[3], argv[4]);
        return 0;
    }/*
    if (strcmp(argv[1], "search")==0 && argc == 4) {

        return 0;
    }
    if (strcmp(argv[1], "searchall")==0 && argc == 5) {

        return 0;
    }*/
    printf("Wrong number of parameters!\n\n");
    printInfo();
    return 0;
}
