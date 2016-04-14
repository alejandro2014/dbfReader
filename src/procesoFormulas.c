#include "procesoFormulas.h"

void procesarLinea(char *linea) {
    printf("Hay que procesar la línea %s\n", linea);
    /*TOKEN *token = NULL;
    free(linea);
    linea = (char *) malloc(100 * sizeof(char));
    sprintf(linea, "ejemplo1 = ((f1 + f2) / f3 - (f1/f4)) * 2 + f5");
    
    minusc((unsigned char *)linea);
    printf("#[%s]\n", linea);
    
    while(linea) {
        token = getToken(linea);
        escribirToken(token);
        borrarToken(token);
    }*/
}

/**
 * Obtiene un token de la cadena y recorta la cadena
 */
TOKEN *getToken(char *linea) {
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    /*ESTADO estado = EST_INICIAL;
    BOOLEANO acabar = FALSO;
    char caracter = '?';
    int desplaz = 0;
    
    char *lineaAux = NULL;
    int longAux = 0;
    
    while(!acabar) {
        caracter = *(linea + (desplaz++));
        
        switch(estado) {
            case EST_INICIAL:
                if(_letra(caracter)) {
                    estado = EST_LEYENDO_CAR;
                } else if(_numero(caracter)) {
                    estado = EST_LEYENDO_NUM;
                } else {
                    switch(caracter) {
                        case ' ': break;
                        case '\t': break;
                        case '=': token->tipo = TIPOTOK_IGUAL; break;
                    }
                }
                break;
            
            case EST_LEYENDO_CAR:
                if(! (_letra(caracter) || _numero(caracter))) {
                    token->tipo = TIPOTOK_CADENA;
                    
                    token->contenido = (char *) malloc((desplaz - 1) * sizeof(char));
                    memcpy(token->contenido, linea, desplaz - 1);
                    *(token->contenido + desplaz - 1) = 0x00;
                    
                    acabar = VERDADERO;
                }
                break;
        }
    }
    
    printf("Linea: [%s]\n", linea);
    printf("Longitud: %i\n", (int)strlen(linea));
    printf("Long. aux: %i\n", longAux);*/
    
    /* Recorta la línea de entrada */
    /*longAux = strlen(linea) - desplaz + 1;
    lineaAux = (char *) malloc(longAux * sizeof(char));
    memcpy(lineaAux, linea + desplaz + 1, longAux);
    free(linea);
    linea = lineaAux;*/
    
    return token;
}

/**
 * Escribe la información de un token en pantalla
 */
void escribirToken(TOKEN *token) {
    printf("-------------------------------\n");
    printf("Tipo: ");
    
    switch(token->tipo) {
        case TIPOTOK_CADENA: printf("cadena\n"); break;
        case TIPOTOK_NUMERO: printf("numero\n"); break;
        case TIPOTOK_SUMA: printf("suma\n"); break;
        case TIPOTOK_RESTA: printf("resta\n"); break;
        case TIPOTOK_MULTIP: printf("multip\n"); break;
        case TIPOTOK_DIVIS: printf("divis\n"); break;
        case TIPOTOK_LPAREN: printf("lparen\n"); break;
        case TIPOTOK_RPAREN: printf("rparen\n"); break;
    }
    
    if(token->tipo == TIPOTOK_CADENA || token->tipo == TIPOTOK_NUMERO) {
        printf("Contenido: [%s]\n", token->contenido);
    }
}

void borrarToken(TOKEN *token) {
    pfree(token->contenido);
    pfree(token);
}
