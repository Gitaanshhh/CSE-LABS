/*
Q2 Send a number using standard send, from the master process to each slave process and print it.
*/

#include <stdio.h>
#include <mpi.h>

void main(int argc, char *argv[]){
    int ierr, rank, size, i;

    ierr = MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if (rank == 0)
        for (i=1; i<size; i++)
            MPI_Send(&i, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    else {
        MPI_Recv(&i, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("%d of %d received %d!\n", rank, size, i);
    }

    MPI_Finalize();
}