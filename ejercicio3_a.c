/*Ejercicio 3 a)*/

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
        printf("Ingrese la cantidad de filas\n");
        scanf("%d", &cantidad_filas);
    }
    //Envio la cantidad de filas que tendra mi matriz a todos los procesos
    MPI_Bcast(&cantidad_filas, 1, MPI_INT, 0, MPI_COMM_WORLD);
    cantidad_columnas = cantidad_filas;
    int matriz[cantidad_filas][cantidad_columnas];
    int vector[cantidad_filas][1];
    int fila[cantidad_columnas];
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
            vector[i][1] = i + 1;
            i++;
        }
    }
    int size = cantidad_columnas * cantidad_filas;
    //Envio el vector a todos los procesos
    MPI_Bcast(&vector, cantidad_filas, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&matriz, cantidad_columnas, MPI_INT, &fila, cantidad_columnas, MPI_INT, 0, MPI_COMM_WORLD);
    
    int i = 0, resultado=0;
    while (i < cantidad_columnas) {
        resultado = resultado + fila[i] * vector[i][1];
        i++;
    }
    printf("Proceso %d: resultado: %d", proceso, resultado);

    /*
    MPI_Send(&mensaje, 1, MPI_CHAR, proximo_proceso, tag, MPI_COMM_WORLD);
    MPI_Bcast(&vueltas, 1, MPI_INT, 0, MPI_COMM_WORLD); //Envia dato a todos los procesos
    MPI_Recv(&mensaje, 1, MPI_CHAR, proceso_anterior, tag, MPI_COMM_WORLD, &status);*/
    MPI_Finalize();
    return(0);
}

