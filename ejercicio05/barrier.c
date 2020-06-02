/*Ejercicio 5
	Comunicaciones Colectivas.
	Implemente cada comunicación colectiva descripta en teoría con comunicaciones punto
	a punto únicamente.
	MPI_Barrier
*/
#include <mpi.h>
#include <stdio.h> 
#include <string.h>
int main(int argc, char** argv) {
    int proceso, total_pro = 0, tag=0, i=1;
    int flag_termine=0, flag_continuar=0;
    
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_pro);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);

    /*	Cada proceso realiza la tarea que este haciendo luego avisa al proceso 0 que termino
		y espera respuesta para poder continuar
    */
    printf("Antes de la barrera proceso %d\n",proceso);
    if (proceso==0){
    	while (i<total_pro){
    		MPI_Recv(&flag_termine, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &status);	
    		i++;
    		printf("Recibi termine de %d\n",flag_termine);
    	}
    	i=1;
    	while (i<total_pro){
    		flag_continuar=1;
    		MPI_Send(&flag_continuar, 1, MPI_INT, i, tag, MPI_COMM_WORLD);	
    		i++;
    		
    	}


    }else{
    	flag_termine=proceso;
    	MPI_Send(&flag_termine, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    	MPI_Recv(&flag_continuar, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    }
    if (flag_continuar==1){
    	printf("despues de la barrera proceso %d\n",proceso);
    }


    MPI_Finalize();
    return(0);

}