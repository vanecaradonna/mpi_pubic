/*Ejercicio 4 manager*/
#include <mpi.h>
int main(int argc, char* argv[]) {
	int world_size = 0, universe_size = 0, universe_sizep = 0, flag=0;
	MPI_Comm everyone; /* intercommunicator */
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	if (world_size != 1) 
		error("Top heavy with management");
	MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_UNIVERSE_SIZE, &universe_sizep, &flag);
	if (!flag) {
		printf("This MPI does not support UNIVERSE_SIZE. How many\n\processes total?");
		scanf("%d", &universe_size);
	}
	else 
		universe_size = *universe_sizep;
	if (universe_size == 1) 
		error("No room to start workers");
	choose_worker_program(worker_program); /* Hace el spawn */
	MPI_Comm_spawn(worker_program, MPI_ARGV_NULL, universe_size - 1, MPI_INFO_NULL, 0, MPI_COMM_SELF, &everyone, MPI_ERRCODES_IGNORE);
	MPI_Finalize();
	return 0;
}
