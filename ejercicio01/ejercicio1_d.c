/*Ejercicio 1 d*/

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
    MPI_Gather(&proceso, 1, MPI_INT, buffer, 1, MPI_INT, 1, MPI_COMM_WORLD);
    if (proceso==1){
        printf("Hola, soy el proceso 1 (hay %d procesos) y recibo: \n", total_pro);
        int i = 0; 
		while(i < total_pro ) {
            printf("Hola desde el proceso %d \n", buffer[i]);
	    	i++;
        }
    }
    MPI_Finalize();
    return(0);
}