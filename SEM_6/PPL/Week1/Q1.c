/*
Q1 Find pow(x, rank) for all ps where x is the int constant and even ranked p prints "Hello" while odd prints "World"

mpicc -o Q1 Q1.c -lm //since we are using math library

*/

#include <stdio.h>
#include <mpi.h>
#include <math.h>

void main(int argc, char *argv[]){
    int ierr, rank, size, res, x = 2;
    ierr = MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("%d of %d is running!\n", rank, size);

    
    res = pow(x, rank);
    printf("pow(%d, %d) is %d\n", x, rank, res);

    if (rank % 2 == 0)
        printf("Hello\n");
    else printf("World!\n");

    MPI_Finalize();
}