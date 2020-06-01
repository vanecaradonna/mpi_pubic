/*Ejercicio 3 

b)  Modifique el código anterior pensando que existen más filas que procesos para tratarlas. 
    Considere dos casos:
    • El número de filas de la matriz es múltiplo de la cantidad de procesos.
    • El número de filas de la matriz no es múltiplo de la cantidad de procesos

*/

#include <mpi.h>
#include <stdio.h> 
#include <string.h>

int main(int argc, char** argv) {
    int proceso, total_pro = 0;
    int cantidad_filas = 1, cantidad_columnas = 1, cantidad_datos = 1;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_pro);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    if (proceso == 0) {
        printf("Ingrese la cantidad de filas\n");
        scanf("%d", &cantidad_filas);
        printf("Ingrese la cantidad de columnas: \n");
        scanf("%d", &cantidad_columnas);
    }
    //Envio la cantidad de filas y columnas que tendra mi matriz a todos los procesos
    MPI_Bcast(&cantidad_filas, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&cantidad_columnas, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int filas_vector= cantidad_columnas;

    int filas_enviadas;
    if (cantidad_filas / total_pro == 0) {
        cantidad_datos = (cantidad_filas / total_pro) * cantidad_filas;
        filas_enviadas = cantidad_filas / total_pro;
    }
    else { //La cantidad de procesos no es multiplo de la cantidad de filas.
        cantidad_datos = ((cantidad_filas / total_pro) + 1) * cantidad_filas;
        filas_enviadas = (cantidad_filas / total_pro) + 1;
    }
    //printf("cantidad de datos=%d\n", cantidad_datos);
    //printf("flias enviadas=%d\n", filas_enviadas);
    
    int matriz[cantidad_filas][cantidad_columnas];
    int vector[filas_vector][1];
    int filas[filas_enviadas][cantidad_columnas];
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
        while (i < filas_vector) {
            vector[i][0] = i + 1;
            //printf("Vector[%d][0]=%d\n ", i, vector[i][0]);
            i++;
            
        }
    }
    int size = cantidad_columnas * cantidad_filas;
    //Envio el vector a todos los procesos
    MPI_Bcast(&vector, filas_vector, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&matriz, cantidad_datos, MPI_INT, &filas, cantidad_datos, MPI_INT, 0, MPI_COMM_WORLD);
    
    int i = 0,j=0, resultado[filas_enviadas][1];
    /*inicializar resultado*/
    while (i < filas_enviadas) {
        resultado[i][0] = 0;
        i++;
    }
    i = 0;
    while (j < filas_enviadas) {
        while (i < cantidad_columnas) { //filas_vector= cantidad_columnas
            //printf("Proceso %d: filas[%d]=%d  vector[%d][0]=%d\n", proceso, i,filas[i],i, vector[i][0]);
            resultado[j][0] = resultado[j][0] + (filas[j][i] * vector[i][0]);
            i++;
        }
        i = 0;
        j++;
    }
        
    ///printf("Proceso %d: resultado: %d\n", proceso, resultado);
    MPI_Gather(&resultado, filas_enviadas, MPI_INT, matriz_resultante, filas_enviadas, MPI_INT, 0, MPI_COMM_WORLD);

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
    MPI_Recv(&mensaje, 1, MPI_CHAR, proceso_anterior, tag, MPI_COMM_WORLD, &status);
    */
    MPI_Finalize();
    return(0);
}

