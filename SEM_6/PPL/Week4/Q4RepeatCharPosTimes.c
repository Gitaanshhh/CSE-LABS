/* 
4. Read a word of length N, using N processes get the output word pattern as shown. Display output in root.
Input : PCAP
Output : PCCAAAPPPP
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

void main(int argc, char *argv[]){
    int rank, size, flag = 1;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char c, s[100];

    if (rank == 0){
        printf("Enter a String of size %d : \n", size);
        scanf("%s", s);                 //One for null char
        if (strlen(s) != size)
            flag = 0;
        // printf("Legal String : %s, %ld\n", s, strlen(s));
    }

    MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(!flag){
        if(rank == 0)
            printf("Too many/less characters.");
        MPI_Finalize();
        exit(1);
    }

    MPI_Scatter(s, 1, MPI_CHAR, &c, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    int repeat = rank + 1;
    char *send_buffer = (char*)malloc((repeat+1) * sizeof(char));

    for (int i = 0; i < repeat; i++)
        send_buffer[i] = c;
    
    send_buffer[repeat] = '\0';

    if (rank == 0) {
        char final_word[100];
        final_word[0] = send_buffer[0];     //since no repeat

        int k = 1;

        for (int i = 1; i < size; i++) {
            MPI_Status status;
            char recv_str[100];
            MPI_Recv(recv_str, i+2, MPI_CHAR, i, i, MPI_COMM_WORLD, &status);   //holds i+1 chars and null char
            for (int j = 0; j < (i + 1); j++)
                if(recv_str[j]!='\0')
                    final_word[k++] = recv_str[j];
        }
        final_word[k] = '\0';
        printf("Output: %s\n", final_word);

    }else{
        MPI_Send(send_buffer, repeat, MPI_CHAR, 0, rank, MPI_COMM_WORLD);
    }

    free(send_buffer);
    MPI_Finalize();
}