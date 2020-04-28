

#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {
    int nodo;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &nodo);

    printf("hello MPI from nodo %d", nodo);
    MPI_Finalize();
    return(0);
}

