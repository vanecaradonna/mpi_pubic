/* worker */
#include <mpi.h>
#include <stdio.h> 
#include <string.h>
int main(int argc, char** argv)
{
	int size;
	MPI_Comm parent;
	MPI_Init(&argc, &argv);
	MPI_Comm_get_parent(&parent);
	if (parent == MPI_COMM_NULL)
		error("No parent!");
	MPI_Comm_remote_size(parent, &size);
	if (size != 1) 
		error("Something's wrong with the parent");
		/*
		* Parallel code here.
		* The manager is represented as the process with rank 0 in (the
		* remote group of) MPI_COMM_PARENT. If the workers need to
		* communicate among themselves, they can use MPI_COMM_WORLD.
		*/
		MPI_Finalize();
	return 0;
}