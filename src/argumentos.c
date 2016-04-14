#include "argumentos.h"

void extraerArgs(int argn, char **argv, char **rutaFicheroDataRed, 
        char **rutaFichVecinas, char **rutaFichBSIC, char **rutaFichMOTOMI) {
    /* Muestra la ayuda */
    if(argn > 1 && !strcmp(argv[1], "-h")) {
        mostrarAyuda(argv[0]);
        exit(0);
    }
}

/**
 * Obtiene un argumento con un nombre determinado de la
 * lista de argumentos
 */
char *extraerArg(int argn, char **argv, char *nombreArg) {
    BOOLEAN encontrado = FALSE;
    int i;
    
    for(i = 0; i < argn && !encontrado; i++) {
        if(!strcmp(argv[i], nombreArg))
            encontrado = TRUE;
    }
    
    if(encontrado && (i < argn))
        return argv[i];
    
    return NULL;
}

/**
 * Muestra la ayuda del programa
 */
void mostrarAyuda(char *nombrePrograma) {

}
