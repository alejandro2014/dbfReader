#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include <bufferedFiles.h>

#include "lectorDbf.h"
#include "procesoFormulas.h"

void mostrarPrompt();
void leerLineaUsuario(char *linea, int longLinea);

#endif
