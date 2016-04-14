#ifndef ARGUMENTOS_H
#define ARGUMENTOS_H

#include <stdlib.h>
#include <string.h>
#include <commonHeader.h>

/* Procesado de los argumentos */
void extraerArgs(int argn, char **argv, char **rutaFicheroDataRed, 
        char **rutaFichVecinas, char **rutaFichBSIC, char **rutaFichMOTOMI);
char *extraerArg(int argn, char **argv, char *nombreArg);
void mostrarAyuda(char *nombrePrograma);

#endif
