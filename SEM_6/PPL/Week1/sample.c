/*
mpicc -o program program.c
mpirun -n 4 ./program
*/

#include <stdio.h>
#include <mpi.h>

void main(int argc, char *argv[]){
    int ierr, rank, size;
    ierr = MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("%d of %d is running!\n", rank, size);


    MPI_Finalize();
}