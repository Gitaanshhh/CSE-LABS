/*
Read N*m values of arr in p0, distribute among N ps, each finds the avg of m values and returns to root which finds the overall avg of it.
*/

#include <stdio.h>
#include <mpi.h>

void main(int argc, char *argv[]){
    int ierr, rank, size, m = 0, A[10], B[10];

    ierr = MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){
        printf("Enter m : ");
        scanf("%d", &m);
        int n = size*m;
        printf("Enter %d values : ", n);
        for (int i=0; i<n; i++)
            scanf("%d", &A[i]);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(A, m, MPI_INT, B, m, MPI_INT, 0, MPI_COMM_WORLD);
    
    float avg = 0.0, avgFinal = 0.0, avgs[size];
    for(int i=0; i<m; i++)
        avg += B[i];

    avg = avg / m;
    
    MPI_Gather(&avg, 1, MPI_FLOAT, avgs, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        for (int i=0; i<size; i++)
            avgFinal += avgs[i];
        avgFinal /= size;
        printf("Avg : %lf\n", avgFinal);
        
    }

    MPI_Finalize();
}