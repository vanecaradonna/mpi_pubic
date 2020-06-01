/*
Ejercicio 2: Anillo.
    Desarrollar un programa MPI denominado “anillo”, en donde los procesos deben hacer
    circular un mensaje a través de un “anillo lógico”. El programa deberá recibir como
    parámetro un entero n que indicará la cantidad de vueltas que el mensaje debe dar al
    anillo. Ejemplo con cuatro procesos:
        El proceso 0 envía el M0 con el dato “A” al proceso 1
        El proceso 1 envía el M1 con el dato “A” al proceso 2
        El proceso 2 envía el M2 con el dato “A” al proceso 3
        El proceso 3 envía el M3 con el dato “A” al proceso 0
    Este proceso será repetido tantas veces como lo indique el parámetro “n”.
*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    int vueltas = -1, i = 0, tag = 10;
    int proceso, total_pro = 0;
    //char mensaje = 'a';
    int mensaje=100;
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
            //MPI_Send(&mensaje, 1, MPI_CHAR, proximo_proceso, tag, MPI_COMM_WORLD);
            //printf("El proceso %d envia el dato %c al proceso %d en el numero de vuelta: %d \n", proceso, mensaje, proximo_proceso, vueltas);
            MPI_Send(&mensaje, 1, MPI_INT, proximo_proceso, tag, MPI_COMM_WORLD);
            printf("El proceso %d envia el dato %d al proceso %d en el numero de vuelta: %d \n", proceso, mensaje, proximo_proceso, vueltas);
        }
        MPI_Bcast(&vueltas, 1, MPI_INT, 0, MPI_COMM_WORLD);


        do {
        	//printf("Entre al while porceso: %d \n",proceso );
            //MPI_Recv(&mensaje, 1, MPI_CHAR, proceso_anterior, tag, MPI_COMM_WORLD, &status);
            MPI_Recv(&mensaje, 1, MPI_INT, proceso_anterior, tag, MPI_COMM_WORLD, &status);
            mensaje=mensaje+1;
            //printf("Soy el proceso %d y recibo en el dato: %c en la vuelta %d\n \n", proceso, mensaje, vueltas);
            
            vueltas--;

            //printf("Hola soy el proceso %d y entre al while con vueltas =%d \n", proceso, vueltas);
            if(!(vueltas==0&&proceso==0)){
            	MPI_Send(&mensaje, 1, MPI_INT, proximo_proceso, tag, MPI_COMM_WORLD);
            	printf("El proceso %d envia el dato %d al proceso %d en el numero de vuelta: %d \n", proceso, mensaje, proximo_proceso, vueltas);/*
            	MPI_Send(&mensaje, 1, MPI_CHAR, proximo_proceso, tag, MPI_COMM_WORLD);
            	printf("El proceso %d envia el dato %c al proceso %d en el numero de vuelta: %d \n", proceso, mensaje, proximo_proceso, vueltas);*/
            }
            /*MPI_Send(&mensaje, 1, MPI_CHAR, proximo_proceso, tag, MPI_COMM_WORLD);
              printf("El proceso %d envia el dato %c al proceso %d en el numero de vuelta: %d \n", proceso, mensaje, proximo_proceso, tag);
			*/
        } while (0 < vueltas);
        printf("Proceso %d termina\n", proceso);
        /*if (proceso == 0) {
            proceso_anterior = total_pro - 1;
            MPI_Recv(&mensaje, 1, MPI_CHAR, proceso_anterior, tag, MPI_COMM_WORLD, &status);
        }*/
    }

    MPI_Finalize();
    return(0);
}

