/*Ejercicio 2*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    int vueltas = -1, i = 0, tag = 10;
    int proceso, total_pro = 0;
    char mensaje = 'a';

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_pro);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);

    int proceso_anterior = (proceso - 1 + total_pro) % total_pro;
    int proximo_proceso = (proceso + 1) % total_pro;

    if (total_pro > 1) {// Tengo mas de 1 proceso
        if (proceso == 0) {
            printf("Ingrese la cantidad de vueltas: \n");
            scanf("%d", &vueltas);
            MPI_Send(&mensaje, 1, MPI_CHAR, proximo_proceso, tag, MPI_COMM_WORLD);
            printf("El proceso %d envia el dato %c al proceso %d en el numero de vuelta: %d \n", proceso, mensaje, proximo_proceso, vueltas);
        }
        MPI_Bcast(&vueltas, 1, MPI_INT, 0, MPI_COMM_WORLD);


        do {
            MPI_Recv(&mensaje, 1, MPI_CHAR, proceso_anterior, tag, MPI_COMM_WORLD, &status);
            //printf("Soy el proceso %d y recibo en el dato: %c en la vuelta %d\n \n", proceso, mensaje, vueltas);
            
            vueltas--;

            //printf("Hola soy el proceso %d y entre al while con vueltas =%d \n", proceso, vueltas);
            if(!(vueltas==1&&proceso==0)){
            	MPI_Send(&mensaje, 1, MPI_CHAR, proximo_proceso, tag, MPI_COMM_WORLD);
            	printf("El proceso %d envia el dato %c al proceso %d en el numero de vuelta: %d \n", proceso, mensaje, proximo_proceso, vueltas);
            }
            /*MPI_Send(&mensaje, 1, MPI_CHAR, proximo_proceso, tag, MPI_COMM_WORLD);
              printf("El proceso %d envia el dato %c al proceso %d en el numero de vuelta: %d \n", proceso, mensaje, proximo_proceso, tag);
			*/
        } while (0 < vueltas);

        /*if (proceso == 0) {
            proceso_anterior = total_pro - 1;
            MPI_Recv(&mensaje, 1, MPI_CHAR, proceso_anterior, tag, MPI_COMM_WORLD, &status);
        }*/
    }

    MPI_Finalize();
    return(0);
}

