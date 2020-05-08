/*Ejercicio 4 manager*/
/* manager */
#include <mpi.h>
int main(int argc, char** argv){
	int world_size, universe_size, * universe_sizep, flag;
	MPI_Comm everyone; /* intercommunicator */
	char worker_program[100];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	if (world_size != 1)
		error("Top heavy with management");
	MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_UNIVERSE_SIZE,&universe_sizep, &flag);
	if (flag == 0)  {
		printf("This MPI does not support UNIVERSE_SIZE\n How many processes total ? \n);
		scanf("%d", &universe_size);
	}
	else
		universe_size = *universe_sizep;
	if (universe_size == 1)
		error("No room to start workers");
	/*
	* Now spawn the workers. Note that there is a runtime
	* determination of what type of worker to spawn, and presumably
	* this calculation must be done at run time and cannot be
	* calculated before starting the program. If everything is
	* known when the application is first started, it is generally
	* better to start them all at once in a single MPI_COMM_WORLD.
	*/
	//choose_worker_program(worker_program);
	MPI_Comm_spawn(worker_program, MPI_ARGV_NULL, universe_size - 1,MPI_INFO_NULL, 0, MPI_COMM_SELF, &everyone,
		MPI_ERRCODES_IGNORE);
	/*
	* Parallel code here. The communicator everyone can be used
	* to communicate with the spawned processes, which have ranks
	* 0,...,MPI_UNIVERSE_SIZE-1 in the remote group of the
	* intercommunicator everyone. An MPI_Bcast using this
	* communicator will broadcast just to the workers.
	*/
	MPI_Finalize();
	return 0;
}
