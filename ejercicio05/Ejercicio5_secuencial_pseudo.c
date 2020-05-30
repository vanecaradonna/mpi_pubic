/*Ejercicio 5 - pseudocodigo secuencial*/
#include <mpi.h>
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>

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
	printf("Ingrese la cantidad de filas\n");
	scanf("%d", &cantidad_filas);
	printf("Ingrese la cantidad de vueltas\n");
	scanf("%d", &cantidad_vueltas);

	int matriz[cantidad_filas][cantidad_filas];
	int matriz_proxima[cantidad_filas][cantidad_filas];
	llenar_matriz(matriz, cantidad_filas);
	while (cantidad_vueltas > k) {
		i = 0;
		while (i < cantidad_filas)
		{
			j = 0;
			while (j < cantidad_filas)
			{
				buscar_vecinos(matriz, vecinos, i, j, cantidad_filas);
				matriz_proxima[i][j] = vive(matriz[i][j], vecinos, cantidad_filas);
				j++;
			}
			i++;
		}
		matriz = matriz_proxima;
		imprimir_matriz(matriz);
		k++;
	}
}

int buscar_vecinos(int matriz[][], int vecinos[], int fila, int columna, int cantidad) {
	/*Esquina superior izquierda*/
	if (fila == 0 && columna == 0) {
		vecinos[0] = matriz[0][1];
		vecinos[1] = matriz[1][1];
		vecinos[2] = matriz[1][0];
		return(3);

	}
	else {
		/*Esquina superior derecha*/
		if (fila == 0 && columna == cantidad - 1) {
			vecinos[0] = matriz[0][cantidad - 2];
			vecinos[1] = matriz[1][cantidad - 2];
			vecinos[2] = matriz[1][cantidad - 1];
			return(3);
		}
		else {
			/*Esquina inferior izquierda */
			if (fila == cantidad - 1 && columna == 0) {
				vecinos[0] = matriz[cantidad - 2][0];
				vecinos[1] = matriz[cantidad - 2][1];
				vecinos[2] = matriz[cantidad - 1][1];
				return(3);
			}
			else {
				/*Esquina inferior derecha */
				if (fila == cantidad - 1 && columna == cantidad - 1) {
					vecinos[0] = matriz[cantidad - 2][cantidad - 2];
					vecinos[1] = matriz[cantidad - 2][cantidad - 1];
					vecinos[2] = matriz[cantidad - 1][cantidad - 2];
					return(3);
				}
				else {
					/*Borde Superior*/
					if (fila == 0) {

						return(5);
					}
				}
			}
		}
	}
}

void llenar_matriz(int matriz[][], int cnt_filas) {
	int i = 0, j = 0, random = 0;

	while (i < cnt_filas)
	{
		j = 0;
		srand(time(NULL));
		while (j < cnt_filas)
		{
			random = rand() % (1 - 0);
			if (random < 0.5) {
				matriz[i][j] = 0;
			}
			else {
				matriz[i][j] = 1;
			}
			j++;
		}
		i++;
	}
}
int vive(int nodo, int vecinos[], int cantidad) {
	int cnt_vecinos_vivos = 0, i = 0;
	while (i < cantidad) {
		if (vecinos[i] == 1) {
			cnt_vecinos_vivos++;
		}
		i++;
	}
	if (nodo == 1) { //La celda esta viva
		if (cnt_vecinos_vivos == 2 || cnt_vecinos_vivos == 3) {
			return(1);
		}
		else {
			return(0);
		}
	}
	else {//La celda esta muerta
		if (cnt_vecinos_vivos == 3) {
			return(1);
		}
		else {
			return(0);
		}
	}

}