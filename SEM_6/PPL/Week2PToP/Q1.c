/*
Q1 Send a word using synchronous send, toggle each letter and send it back
mpicc -o Q1 Q1.c

*/

#include <stdio.h>
#include <string.h>
#include <mpi.h>

void main(int argc, char *argv[]){
    int ierr, rank, size;
    char str[40];

    ierr = MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    // printf("%d of %d is running!\n", rank, size);

    if (rank == 0){
        printf("Enter a String : ");
        scanf("%s", str);
        
        MPI_Ssend(str, sizeof(str), MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(str, sizeof(str), MPI_CHAR, 1, 1, MPI_COMM_WORLD, &status);
        printf("New String : %s\n",str);
    }
    else {
        MPI_Recv(str, sizeof(str), MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

        for (int i=0; i<strlen(str); i++){
            if (str[i] >= 'a' & str[i] <= 'z')
                str[i] -= 32;
            else str[i] += 32;
        }

        MPI_Ssend(str, sizeof(str), MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}