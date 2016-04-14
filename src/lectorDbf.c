/**
 * Operaciones realizadas con un fichero de formato DBF
 * @author Alejandro
 */
#include "lectorDbf.h"

/**
 * Carga de un dbf en memoria y las estructuras necesarias
 * para gestionarlo
 */
FICHERODBF *abrirDBF(char *ruta) {
    FICHERODBF *ficheroDBF = _pmalloc(FICHERODBF, 1);
    char tipoDBF = 0x00;
    
    ficheroDBF->fichero = BF_open(ruta, READING);
    tipoDBF = *(ficheroDBF->fichero->content);
    
    /* Carga la cabecera en función del tipo de DBF */
    switch(tipoDBF) {
        case 0x03:
            ficheroDBF->cabecera = (unsigned char *) malloc(sizeof(CABEC_DBF5));
            memcpy(ficheroDBF->cabecera, ficheroDBF->fichero->content, sizeof(CABEC_DBF5));
            ficheroDBF->tablaLocaliz = componerTablaLocaliz(ficheroDBF);
            break;
            
        default:
            printf("[Error] Archivo DBF no reconocido (%x)\n", tipoDBF);
            BF_close(ficheroDBF->fichero);
            pfree(ficheroDBF);
            break;
    }
	
	return ficheroDBF;
}

/**
 * Crea una tabla de la base de datos con los campos determinados
 */
void crearTabla(char *nombreTabla, CAMPO_DBF5 *arrCampos, int numCampos) {
    FILE *fichSalida = fopen(nombreTabla, "wb");
    CABEC_DBF5 DBFheader;
    int sumaBytesCampos = 0;
    int i;
    
    memset(&DBFheader, 0, sizeof(DBFheader));
    DBFheader.version = 0x03;
    DBFheader.numRegistros = 0;
    DBFheader.bytePrimerRegistro = sizeof(DBFheader);
    
    for(i = 0; i < numCampos; i++)
        sumaBytesCampos += (arrCampos + i)->longitud;
        
    DBFheader.numBytesRegistro = sumaBytesCampos;
    
    /* Escribe en el fichero de salida */
    fwrite(&DBFheader, sizeof(DBFheader), 1, fichSalida);
    fwrite(arrCampos, sizeof(CAMPO_DBF5), numCampos, fichSalida);
    
    fclose(fichSalida);
}

/**
 * Obtiene la tabla necesaria para poder hacer consultas
 * sobre el DBF en cuestión
 * @return Tabla de localización, NULL si hay error
 */
TABLA_LOCALIZ *componerTablaLocaliz(FICHERODBF *ficheroDBF) {
    FILA_LOCALIZ *filaLocaliz = NULL;
	CAMPO_DBF5 *campoActual;

	char terminCampos = 'X';
	int desplaz = sizeof(CABEC_DBF5);
	int i, j;
	int numCamposDBF = 0;
	unsigned int despRelativo = 0;
    
    /* TODO Adaptarlo a otros tipos de DBF */
	/* Cuenta de los campos del DBF */
	while(terminCampos != 0x0d) {
		desplaz += sizeof(CAMPO_DBF5);
		numCamposDBF++;
		terminCampos = *(ficheroDBF->fichero->content + desplaz);
	}
    
	/* Elabora una tabla auxiliar para facilitar la búsqueda */
	ficheroDBF->campos = (unsigned char *) malloc(numCamposDBF * sizeof(CAMPO_DBF5));
    memcpy(ficheroDBF->campos, ficheroDBF->fichero->content + sizeof(CABEC_DBF5), 
           numCamposDBF * sizeof(CAMPO_DBF5));
    
	for(i = 0; i < numCamposDBF; i++)
        lowercase(((CAMPO_DBF5 *)ficheroDBF->campos)[i].nombre);
        
	/* Crea la tabla de localización */
	ficheroDBF->tablaLocaliz = (TABLA_LOCALIZ *) malloc(sizeof(TABLA_LOCALIZ));
    ficheroDBF->tablaLocaliz->numCampos = numCamposDBF;
	ficheroDBF->tablaLocaliz->filas = (FILA_LOCALIZ *) malloc(numCamposDBF * sizeof(FILA_LOCALIZ));
		
    for(j = 0; j < numCamposDBF; j++) {
        filaLocaliz = ficheroDBF->tablaLocaliz->filas + j;
        campoActual = (CAMPO_DBF5 *)ficheroDBF->campos + j;
            
        memcpy(filaLocaliz->nombre, campoActual, 11);
        filaLocaliz->direcRel = despRelativo;
        filaLocaliz->longitud = campoActual->longitud;
        filaLocaliz->tipo = campoActual->tipo;
        filaLocaliz->decimales = campoActual->decimales;
                
        /*printf("%s %i %i %c %i\n", filaLocaliz->nombre, filaLocaliz->direcRel,
            filaLocaliz->longitud, filaLocaliz->tipo, filaLocaliz->decimales);*/
			
		despRelativo += campoActual->longitud;
	}
	
	return ficheroDBF->tablaLocaliz;
}

/**
 * Liberación del espacio reservado por el DBF
 */
int cerrarDBF(FICHERODBF *ficheroDBF) {    
    pfree(ficheroDBF->cabecera);
    pfree(ficheroDBF->campos);
    pfree(ficheroDBF->tablaLocaliz->filas);
    pfree(ficheroDBF->tablaLocaliz);
    BF_close(ficheroDBF->fichero);
    pfree(ficheroDBF);
    return 0;
}

/**
 * Selecciona un conjunto de campos de un fichero DBF
 */
void seleccionar(FICHERODBF *ficheroDBF, char **camposArray, int numCamposArray) {
    CABEC_DBF5 *cabecera = _pmalloc(CABEC_DBF5, 1);
    TABLA_LOCALIZ *tablaLocaliz = ficheroDBF->tablaLocaliz;
    FILA_LOCALIZ *campoActualDBF = NULL;
    char *bufferSalida = _pmalloc(char, 40);
    char *campoActualArray = NULL;
    int numCamposDBF  = tablaLocaliz->numCampos;
    int numFilasDBF = cabecera->numRegistros;
    int *arrDesplazam = _pmalloc(int, numCamposArray);
    int *arrLongit = _pmalloc(int, numCamposArray);
    int i, j;
    
    int desplazActual = cabecera->bytePrimerRegistro + 1;
    int longRegistro = cabecera->numBytesRegistro;
    
    numFilasDBF = 5;
    /* printf("Desplazamiento inicial: %i\n", desplazActual); */
    /*memset(arrDesplazam, 0, longArrNum);
    memset(arrLongit, 0, longArrNum);*/
    
    /* Localiza las posiciones de los campos que hay que buscar */
    for(i = 0; i < numCamposArray; i++) {
        campoActualArray = camposArray[i];
        
        for(j = 0; j < numCamposDBF; j++) {
            campoActualDBF = tablaLocaliz->filas + j;
            
            if(!strcmp(campoActualDBF->nombre, campoActualArray)) {
                arrDesplazam[i] = campoActualDBF->direcRel;
                arrLongit[i] = campoActualDBF->longitud;
            }
        }
    }
    
    /* Selecciona los campos que quiere buscar el usuario */
    for(i = 0; i < numFilasDBF; i++) {
        for(j = 0; j < numCamposArray; j++) {
            memcpy(bufferSalida, ficheroDBF->fichero->content + desplazActual + 
                    arrDesplazam[j], arrLongit[j]);
            *(bufferSalida + arrLongit[j]) = 0x00;
            printf("%s\t", bufferSalida);
        }
        
        printf("\n");
        desplazActual += longRegistro;
    }
    
    pfree(bufferSalida);
}
