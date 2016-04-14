#Script created automatically on Tue Nov  6 21:58:51 GMT 2012

EXE=dbfReader
CC=gcc

MAINDIR=/home/alejandro/programs/lectorDbf
SRCPATH=${MAINDIR}/src
OBJPATH=${MAINDIR}/obj
BINPATH=${MAINDIR}/bin

OPTC=-c -I/home/alejandro/programs/lib/include -g
OPTL=-L/home/alejandro/programs/lib/bin -lutilities -g

OBJ1=argumentos
OBJ2=lectorDbf
OBJ3=main
OBJ4=procesoFormulas
OBJ= ${OBJPATH}/${OBJ1}.o ${OBJPATH}/${OBJ2}.o ${OBJPATH}/${OBJ3}.o ${OBJPATH}/${OBJ4}.o

${BINPATH}/${EXE}: ${OBJ}
	${CC} ${OBJ} -o ${BINPATH}/${EXE} ${OPTL}

${OBJPATH}/argumentos.o: ${SRCPATH}/argumentos.c
	${CC} -c ${SRCPATH}/argumentos.c -o ${OBJPATH}/argumentos.o ${OPTC}

${OBJPATH}/lectorDbf.o: ${SRCPATH}/lectorDbf.c
	${CC} -c ${SRCPATH}/lectorDbf.c -o ${OBJPATH}/lectorDbf.o ${OPTC}

${OBJPATH}/main.o: ${SRCPATH}/main.c
	${CC} -c ${SRCPATH}/main.c -o ${OBJPATH}/main.o ${OPTC}

${OBJPATH}/procesoFormulas.o: ${SRCPATH}/procesoFormulas.c
	${CC} -c ${SRCPATH}/procesoFormulas.c -o ${OBJPATH}/procesoFormulas.o ${OPTC}
clean:
	rm -f ${OBJPATH}/* ${BINPATH}/${EXE}
