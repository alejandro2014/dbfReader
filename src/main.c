#include "main.h"

int main(int argn, char **argv) {
    FICHERODBF *ficheroDBF = NULL;
    char *columnas1[] = {"f2", "f5", "f4"};
    char *columnas2[] = {"f1", "f2", "f3", "f4", "f5"};
    char *columnas3[] = {"f5"};
    char *columnas4[] = {"f2", "f3"};
    CAMPO_DBF5 *arrCampos = NULL;
            
    ficheroDBF = abrirDBF("/home/alejandro/programs/lectorDbf/dat/dbf3Prueba.dbf");
       // "/home/alejandro/programas/lectorDbf/lectorDbf/dbf3Prueba.dbf");
    seleccionar(ficheroDBF, columnas1, 3);
    seleccionar(ficheroDBF, columnas2, 5);
    seleccionar(ficheroDBF, columnas3, 1);
    seleccionar(ficheroDBF, columnas4, 2);
    cerrarDBF(ficheroDBF);

    arrCampos = _pmalloc(CAMPO_DBF5, 2);
    
    sprintf((arrCampos + 0)->nombre, "campo1");
    (arrCampos + 0)->tipo = 'N';
    (arrCampos + 0)->longitud = 5;
    (arrCampos + 0)->decimales = 0;
    
    sprintf((arrCampos + 1)->nombre, "field2");
    (arrCampos + 1)->tipo = 'C';
    (arrCampos + 1)->longitud = 10;
    (arrCampos + 1)->decimales = 0;
    
    crearTabla("nuevaTabla", arrCampos, 2);
    /*BOOLEAN acabar = FALSE;
    int longLinea = 100;
    char *lineaLeida = _pmalloc(char, longLinea);
    
    while(!acabar) {
        mostrarPrompt();
        leerLineaUsuario(lineaLeida, longLinea);
        if(strcmp(lineaLeida, "exit")) {
            procesarLinea(lineaLeida);
        } else
            acabar = TRUE;
    }
    
    pfree(lineaLeida);*/
    
    return 0;
}

void mostrarPrompt() {
    printf("> ");
}

void leerLineaUsuario(char *linea, int longLinea) {
    char *posIntro = NULL;
    
    if(fgets(linea, longLinea, stdin)) {
        posIntro = strchr(linea, '\n');
        
        if(posIntro) *posIntro = 0x00;
    } else
        linea = NULL;
}
