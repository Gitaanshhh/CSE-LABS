/*
Read N values of arr in p0, distribute among N ps, each finds the sq and returns to root
*/

#include <stdio.h>
#include <mpi.h>

void main(int argc, char *argv[]){
    int ierr, rank, size, n, A[10], B[10], x;

    ierr = MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){
        n = size;
        printf("Enter %d values : ", n);
        for (int i=0; i<n; i++)
            scanf("%d", &A[i]);
    }

    MPI_Scatter(A, 1, MPI_INT, &x, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    printf("%d Received : %d\n", rank, x);
    x = x*x;
    
    MPI_Gather(&x, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        printf("Result gathered in the root : \n");
        for (int i=0; i<n; i++)
            printf("%d\t", B[i]);
    }

    MPI_Finalize();
}