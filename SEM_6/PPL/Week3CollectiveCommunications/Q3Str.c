/*
3. Read a string. Use N processes (string length is evenly divisible by N). Find the number of non-vowels in the string. 
In root process print number of non-vowels found by each process and print the total number of non-vowels
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

void main(int argc, char *argv[]){
    int ierr, rank, size, m = 0, count = 0, flag = 1;

    ierr = MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char s[100], tempS[100], vowels[] = "aeiouAEIOU";

    if (rank == 0){
        printf("Enter a String : \n");
        scanf("%s", s);   
        if (strlen(s) % size != 0)
            flag = 0;
        m = strlen(s) / size;
    }

    MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(!flag){
        if(rank == 0)
            printf("Too many/less characters.");
        MPI_Finalize();
        exit(1);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(s, m, MPI_CHAR, tempS, m, MPI_CHAR, 0, MPI_COMM_WORLD);
    // tempS[m] = '\0';
    for(int i=0; i<m; i++){
        flag = 1;
        for (int j=0; j<strlen(vowels); j++)
            if (tempS[i] == vowels[j]){
                flag = 0;
                break;
            }
        if (flag) 
            count ++;  
    }
    int counts[m];
    MPI_Gather(&count, 1, MPI_INT, counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        int s = 0;
        for (int i=0; i<size; i++){
            s += counts[i];
            printf("%d found %d non vowels\n", i, counts[i]);
        }
        printf("Total number of Non Vowels : %d\n", s);
    }

    MPI_Finalize();
}
