#ifndef LECTOR_DBF
#define LECTOR_DBF

#include <stdlib.h>
#include <bufferedFiles.h>
#include <commonHeader.h>
#include <pstrings.h>
/*#include "cabComun.h"
#include "cadenas.h"*/

/* Header of the DBF file */
typedef struct {
	unsigned char version;
	unsigned char fecha[3];
	int numRegistros;
	unsigned short bytePrimerRegistro;
	unsigned short numBytesRegistro;
	unsigned char reservado[20];
} CABEC_DBF5;

/* Field of the DBF file */
typedef struct {
	char nombre[11];
	char tipo;
	int reservado1;
	char longitud;
	char decimales;
	unsigned char reservado2[14];
} CAMPO_DBF5;

typedef struct {
	char nombre[11];
	int direcRel;
	unsigned char longitud;
	unsigned char tipo;
	unsigned char decimales;
} FILA_LOCALIZ;

typedef struct {
	int numCampos;
	int numRegistros;
	char *inicioDatos;
	FILA_LOCALIZ *filas;
} TABLA_LOCALIZ;

typedef struct {
    char **columna;
} COLUMNA_RESUL;

typedef struct {
    char tipoDBF;
    unsigned char *cabecera;
    unsigned char *campos;
    BF_FILE *fichero;
    TABLA_LOCALIZ *tablaLocaliz;
} FICHERODBF;

/* Operaciones que se realizan sobre los DBF */
FICHERODBF *abrirDBF(char *ruta);
int cerrarDBF(FICHERODBF *fichero);
void crearTabla(char *nombreTabla, CAMPO_DBF5 *arrCampos, int numCampos);
void seleccionar(FICHERODBF *ficheroDBF, char **campos, int numCamposArray);

TABLA_LOCALIZ *componerTablaLocaliz(FICHERODBF *ficheroDBF);

#endif
