/*
Read N values of arr in p0, distribute among N ps, each finds the factorial and returns to root which finds the sum of it.
*/

#include <stdio.h>
#include <mpi.h>

void main(int argc, char *argv[]){
    int ierr, rank, size, n, A[10], B[10], x, fact = 1, sum = 0;

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
    
    for (int i=1; i<=x; i++)
        fact = fact * i;
    
    
    MPI_Gather(&fact, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        for (int i=0; i<n; i++)
            sum += B[i];
        printf("Sum : %d\n", sum);
        
    }

    MPI_Finalize();
}