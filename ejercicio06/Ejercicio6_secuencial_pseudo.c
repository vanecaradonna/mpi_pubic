/*Ejercicio 5 - pseudocodigo secuencial
a) 	Analice el problema planteado. ¿Considera que es posible encontrar una solución
	paralela para el mismo? Justifique su respuesta.
	Se puede utilizar una implementacion paralela dividiendo la matriz dependiendo la cantidad
	de procesos que tenga. Considerando que ademas de enviar las posiciones a calcular enviamos 
	tambien los bordes la submatriz para que cada nodo pueda calcular los vecinos de sus celular.

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