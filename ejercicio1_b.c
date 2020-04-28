/*Ejercicio 1 b*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    int proceso, total_pro;
    char mensaje[30] = "Saludos desde el proceso ";
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_pro);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    if (proceso == 0) {
        MPI_Status status;
        int i = 0;
        for (; i < total_pro - 1; i++) {// Recepcion de los mensajes.

            MPI_Recv(&mensaje, 30, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Hola, soy el proceso 0 y recibo: %s%d \n", mensaje, status.MPI_SOURCE);

        }
    }
    else { //Genero el saludo al proceso 0
        MPI_Send(&mensaje, strlen(mensaje), MPI_CHAR, 0, proceso, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return(0);
}