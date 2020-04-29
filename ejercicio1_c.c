/*Ejercicio 1 c*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char **argv) {
    int proceso, total_pro=0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_pro);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    int buffer[total_pro - 1];
    // Recepcion de los mensajes.
    MPI_Gather(&proceso, 1, MPI_INT, buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (proceso==0){
        printf("Hola, soy el proceso 0 (hay %d procesos) y recibo: %d \n", &total_pro);
        for (int i = 0; i < total_pro - 1;i++) {
            printf("Hola desde el proceso %d \n", buffer[i]);
        }
	}
    MPI_Finalize();
    return(0);
}
