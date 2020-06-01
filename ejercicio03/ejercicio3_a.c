/*
Ejercicio 3 Multiplicación de matriz por un vector.
    Analizar diferentes soluciones paralelas para resolver la multiplicación de una matriz por
    un vector. Analice soluciones paralelas considerando los distintos tipos de particionado
    de datos.
    a)  Resuelva el problema planteado considerando que cada proceso realiza la
        multiplicación de una fila de la matriz por el vector completo. Considera en la solución
        el siguiente esquema de código:
            1. El proceso 0 generará la matriz y el vector.
            2. Las filas de la matriz se repartirán entre los procesos participantes.
            3. El vector se replicará en los procesos.
            4. Cada proceso realizará las operaciones que le corresponden.
            5. El vector resultado es reunido por el proceso 0.
            6. El proceso 0 mostrará el resultado.
        Observación: El programa debe ser parametrizable, es decir que el mismo debe solicitar
        el tamaño de la matriz antes de generarla. Asuma el caso más simple donde cuenta con
        tantos procesos como filas tenga la matriz.
*/

#include <mpi.h>
#include <stdio.h> 
#include <string.h>

int main(int argc, char** argv) {
    int proceso, total_pro = 0;
    int cantidad_filas = 1, cantidad_columnas = 1;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_pro);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    if (proceso == 0) {
        printf("Ingrese la cantidad de filas: \n");
        scanf("%d", &cantidad_filas);
        printf("Ingrese la cantidad de columnas: \n");
        scanf("%d", &cantidad_columnas);
    }
    //Envio la cantidad de filas que tendra mi matriz a todos los procesos
    MPI_Bcast(&cantidad_filas, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&cantidad_columnas, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int filas_vector= cantidad_columnas;
   // cantidad_columnas = cantidad_filas;
    int matriz[cantidad_filas][cantidad_columnas];
    int vector[cantidad_columnas][1];
    int fila[cantidad_columnas];
    int matriz_resultante[cantidad_filas][1];
    //Lleno la matriz y el vector
    if (proceso == 0) {
        int i = 0, j = 0, contador = 1;
        while (i < cantidad_filas) {
            j = 0;
            while (j < cantidad_columnas) {
                matriz[i][j] = contador;
                contador++;
                j++;
            }
            i++;
        }
        i = 0;
        while (i < cantidad_filas) {
            vector[i][0] = i + 1;
            //printf("Vector[%d][0]=%d\n ", i, vector[i][0]);
            i++;
            
        }
    }
    int size = cantidad_columnas * cantidad_filas;
    //Envio el vector a todos los procesos
    MPI_Bcast(&vector, filas_vector, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&matriz, cantidad_columnas, MPI_INT, &fila, cantidad_columnas, MPI_INT, 0, MPI_COMM_WORLD);
    
    int i = 0, resultado=0;
    while (i < cantidad_columnas) { //filas_vector = cantidad_columnas
        //printf("Proceso %d: fila[%d]=%d  vector[%d][0]=%d\n", proceso, i,fila[i],i, vector[i][0]);
        resultado = resultado + (fila[i] * vector[i][0]);
        i++;
    }
    //printf("Proceso %d: resultado: %d\n", proceso, resultado);
    MPI_Gather(&resultado, 1, MPI_INT, matriz_resultante, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (proceso == 0) {
        int k = 0;
        printf("La matriz resultante es: \n");
        while (k < cantidad_filas) {
            printf("|%d|\n", matriz_resultante[k][0]);
            k++;
        }
    }
    /*
    MPI_Send(&mensaje, 1, MPI_CHAR, proximo_proceso, tag, MPI_COMM_WORLD);
    MPI_Bcast(&vueltas, 1, MPI_INT, 0, MPI_COMM_WORLD); //Envia dato a todos los procesos
    MPI_Recv(&mensaje, 1, MPI_CHAR, proceso_anterior, tag, MPI_COMM_WORLD, &status);*/
    MPI_Finalize();
    return(0);
}

