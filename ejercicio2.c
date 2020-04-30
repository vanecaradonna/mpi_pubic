/*Ejercicio 2*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char** argv) {
    int vueltas=-1, i=0;
    int proceso, total_pro = 0;
    char mensaje = 'a';
    int proceso_anterior;
    int proximo_proceso=-1;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_pro);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);

    printf("Antes de transmitir. Numero de vueltas: %d, soy el proceso %d", vueltas, proceso);
    if (total_pro > 1) {// Tengo mas de 1 proceso
        if (vueltas == -1) {
            printf("Ingrese la cantidad de vueltas: \n");
            scanf("%d", &vueltas);
            MPI_Bcast(&vueltas, 1, MPI_INT, proceso, MPI_COMM_WORD);
            printf("Transmiti numero de vueltas. Soy el proceso %d, y la cantidad de vueltas es %d", proceso, vueltas);
        }

        printf("Despues  de transmitir. Numero de vueltas: %d, soy el proceso %d", vueltas, proceso);
        /*do{
            printf("numero de vuelta %d\n",vueltas);
            if (proceso == 0) {
                proceso_anterior = total_pro - 1;
                printf("Desconte vuelta\n");
                i++;
            }
            else {
                proceso_anterior = proceso - 1;
            }
            MPI_Recv(&mensaje, 1, MPI_CHAR, proceso_anterior, proceso_anterior, MPI_COMM_WORLD, &status);
            if (proceso == total_pro - 1) {
                proximo_proceso = 0;
            }
            else {
                proximo_proceso = proceso + 1;
            }
            MPI_Send(&mensaje, 1, MPI_CHAR, proximo_proceso, proceso, MPI_COMM_WORLD);
            printf("El proceso %d envia el dato %c al proceso %d\n", proceso, mensaje, proximo_proceso);
        
        } while (i < vueltas);

        if (proceso == 0) {
            proceso_anterior = total_pro - 1;
            MPI_Recv(&mensaje, 1, MPI_CHAR, proceso_anterior, proceso_anterior, MPI_COMM_WORLD, &status);
        }*/
    }
   // printf("sali del while\n");
    MPI_Finalize();
    return(0);
}

