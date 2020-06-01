/*
Ejercicio 1: Hello World.
	a) El siguiente código resuelve un saludo en paralelo de todos los procesos que trabajan en paralelo:
	Ejecutar  el programa para distinta cantidad de procesos. Analizar la salida  de  las ejecuciones  y 
	compararlas entre ellas.
*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int nodo;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &nodo);

    printf("hello MPI from nodo %d", nodo);
    MPI_Finalize();
    return(0);
}

