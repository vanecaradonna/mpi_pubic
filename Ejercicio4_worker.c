/* worker */
#include <mpi.h>
int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	MPI_Comm_get_parent(&parent);
	if (parent == MPI_COMM_NULL)
		error("No parent!");
	MPI_Comm_remote_size(parent, &size);
	if (size != 1)
		error("Something's wrong with the parent");
	MPI_Finalize();
	return 0;
}