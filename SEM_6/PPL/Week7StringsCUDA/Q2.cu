/*
2. Write a CUDA program that reads a string § and produces the string RS as follows:
Input string §: PCAP
Output string RS: PCAPPCAPCP
Note: Each work item copies required number of characters from § in RS.
*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

__global__ void CUDACount(char* A, char *R, int n){
    int i = threadIdx.x;
    // int offset = 0;
    // for (int k=0; k<i; k++)
    //     offset += n-k;
    int offset = i * n - (i * (i - 1)) / 2; // n + (n-1) + .. n-(i-1)
    for (int j=0; j<n-i; j++)
        R[offset+j] = A[j];
}        

int main() {
    char A[N];
    char *R, *d_A, *d_R;
    int n, fn = 0;

    printf("Enter a string : ");
    fgets(A, N, stdin);
    A[strcspn(A, "\n")] = 0;
    n = strlen(A);

    // for (int i=0; i<n; i++)
    //     fn += n-i;
    fn = n * (n + 1) / 2; //n + n-1 + ... + 1

    R = (char *) malloc((fn+1)*sizeof(char));

    cudaMalloc((void**)&d_A, strlen(A)*sizeof(char));
    cudaMalloc((void**)&d_R, fn*sizeof(char));

    cudaMemcpy(d_A, A, strlen(A), cudaMemcpyHostToDevice);
    
    CUDACount<<<1,n>>>(d_A, d_R, n);
    cudaDeviceSynchronize();

    cudaMemcpy(R, d_R, fn*sizeof(char), cudaMemcpyDeviceToHost);
    R[fn] = '\0';

    printf("Final String = %s\n", R);

    cudaFree(d_A);
    cudaFree(d_R);
    free(R);
    return 0;
}