/*Ejercicio 5 - pseudocodigo MPI

b) 	Realice una implementación del juego de a vida de manera secuencial y otra en forma
	paralela utilizando MPI. Ambas implementaciones serán en pseudocódigo.
	Considere que el estado inicial es generado aleatoriamente por el programa. Se debe
	parametrizar el tamaño de la matriz y el número de ciclos que ejecutará el juego


*/
#include <mpi.h>
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
Recibe el nodo actual, los vecinos y la cantidad de los mismos y devuelve si la celda devuelve:
	1: Si la celda vive
	0: si la celda muere
*/
int vive(int, int[], int);

/*LLena la mariz de manera aleatoria*/
void llenar_matriz(int[][], int);

/*guarda los vecinos de un determinado nodo, devuelve la cantidad de vecinos*/
int buscar_vecinos(int[][], int[], int, int, int);

int main(int argc, char** argv) {
	int cantidad_filas = 0, vecinos[8], j = 0, i = 0, k = 0, cantidad_vueltas = 0;
	MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_pro);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    if (proceso==0){
    	printf("Ingrese la cantidad de filas\n");
		scanf("%d", &cantidad_filas);
		printf("Ingrese la cantidad de vueltas\n");
		scanf("%d", &cantidad_vueltas);

    }
    cantidad_columnas=cantidad_filas;
	//Envio la cantidad de filas y columnas que tendra mi matriz a todos los procesos
    MPI_Bcast(&cantidad_filas, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int matriz[cantidad_filas][cantidad_filas];
	int matriz_proxima[cantidad_filas][cantidad_filas];

	if (proceso==0){
		llenar_matriz(matriz, cantidad_filas);
	}
	int filas_enviadas; //Envio una mas de la que me corresponde.
    if (cantidad_filas / total_pro == 0) {
        cantidad_datos = (cantidad_filas / total_pro) * cantidad_filas;
        filas_enviadas = cantidad_filas / total_pro + 1 ;
    }
    else { //La cantidad de procesos no es multiplo de la cantidad de filas.
        cantidad_datos = ((cantidad_filas / total_pro) + 1) * cantidad_filas;
        filas_enviadas = (cantidad_filas / total_pro) + 1 +1;
    }
	
	int filas[filas_enviadas][cantidad_columnas];
	int filas_proximas[filas_enviadas][cantidad_columnas];
	int size = cantidad_columnas * cantidad_filas;

	while (cantidad_vueltas > k) {

		MPI_Scatter(&matriz, cantidad_datos, MPI_INT, &filas, cantidad_datos, MPI_INT, 0, MPI_COMM_WORLD);

		i = 0;
		while (i < filas_enviadas-1)
		{
			j = 0;
			while (j < filas_enviadas-1)
			{
				buscar_vecinos(filas, vecinos, i, j, filas_enviadas);
				filas_proximas[i][j] = vive(filas[i][j], vecinos, filas_enviadas);
				j++;
			}
			i++;
		}


		MPI_Gather(&filas_proximas, filas_enviadas, MPI_INT, matriz_resultante, filas_enviadas, MPI_INT, 0, MPI_COMM_WORLD);
		matriz = matriz_proxima;
		if (proceso==0){
			imprimir_matriz(matriz);
		}
		k++;
	}
	MPI_Finalize();
    return(0);
}