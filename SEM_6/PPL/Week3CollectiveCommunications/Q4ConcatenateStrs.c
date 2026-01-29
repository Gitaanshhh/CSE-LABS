/*
3. Read 2 strings of same len. Use N processes (string length is evenly divisible by N), produce the resultant string as shown.
Display result in the root process. Use collective comunication routines.
Example :
String 1 : string
String 2 : length
Resultant String : slternigntgh
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

void main(int argc, char *argv[]){
    int ierr, rank, size, m = 0, flag = 1, k = 0;

    ierr = MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char s1[100], s2[100], tempS[100], tempRes[100], res[100];

    if (rank == 0){
        printf("Enter String 1 : \n");
        scanf("%s", s1);   
        printf("Enter String 2 : \n");
        scanf("%s", s2);   
        if (strlen(s1) != strlen(s2) | strlen(s1) % size != 0)
            flag = 0;
        m = strlen(s1) / size;
    }

    MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(!flag){
        if(rank == 0)
            printf("Unequal OR not evenly divisible Strings Entered!");
        MPI_Finalize();
        exit(1);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(s1, m, MPI_CHAR, tempS, m, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(s2, m, MPI_CHAR, tempS + m, m, MPI_CHAR, 0, MPI_COMM_WORLD);
    
    for (int i = 0; i < m; i++) {
        tempRes[k++] = tempS[i];
        tempRes[k++] = tempS[i + m];
    }
        
    MPI_Gather(tempRes, 2 * m, MPI_CHAR, res, 2 * m, MPI_CHAR, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("Resultant String : %s\n", res);

    MPI_Finalize();
}
