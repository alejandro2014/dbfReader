#ifndef PROCESO_FORMULAS_H
#define PROCESO_FORMULAS_H

#include <stdio.h>
#include <stdlib.h>
#include <pstrings.h>
/*#include "cadenas.h"*/

#define TIPOTOK_CADENA 0x00
#define TIPOTOK_NUMERO 0x01
#define TIPOTOK_SUMA 0x02
#define TIPOTOK_RESTA 0x03
#define TIPOTOK_MULTIP 0x04
#define TIPOTOK_DIVIS 0x05
#define TIPOTOK_LPAREN 0x06
#define TIPOTOK_RPAREN 0x07
#define TIPOTOK_IGUAL 0x08

typedef char TIPOTOKEN;

#define EST_INICIAL 0x00
#define EST_LEYENDO_CAR 0x01
#define EST_LEYENDO_NUM 0x02

typedef char ESTADO;

typedef struct {
    TIPOTOKEN tipo;
    char *contenido;
} TOKEN;

void procesarLinea(char *linea);
TOKEN *getToken(char *linea);
void escribirToken(TOKEN *token);
void borrarToken(TOKEN *token);

#endif
