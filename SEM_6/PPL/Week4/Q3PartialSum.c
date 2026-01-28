/* 
3. Read a 4 X 4 Matrix. Display partial sum.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void main(int argc, char *argv[]){
    int rank, size, arr[4][4], row[4], result_row[4];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 4){
        if(rank == 0)
            printf("Only 4 processes can execute this program\n");
        MPI_Finalize();
        exit(0);
    }

    if (rank == 0){
        printf("Enter the 16 elements ROW wise : \n");
        for (int i=0; i<4; i++)
            for (int j=0; j<4; j++)
                scanf("%d", &arr[i][j]);
    }
    
    //Sends rows
    MPI_Scatter(arr, 4, MPI_INT, row, 4, MPI_INT, 0, MPI_COMM_WORLD);

    //Calcs partial sum of rows
    MPI_Scan(row, result_row, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    int output_matrix[4][4];
    MPI_Gather(result_row, 4, MPI_INT, output_matrix, 4, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Output Matrix:\n");
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) 
                printf("%d ", output_matrix[i][j]);
            printf("\n");
        }
    }

    MPI_Finalize();

}