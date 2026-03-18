/*
1. Write a program in CUDA to count the number of times a given word is repeated in a sentence.
(Use Atomic function)
*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

__global__ void CUDACount(char* s, char* w, int*indices, int *d_c, int n, int m){
    int i = threadIdx.x; //int i = blockIdx.x * blockDim.x + threadIdx.x;
    int start = indices[i];
    int flag = 1;
 
    if (start + m > n) 
        return;

    for (int j = 0; j<m;j ++){
        if (s[start + j] != w[j]){
            flag = 0;
            break;
        }
    }
    if (flag && (s[indices[i] + m] == ' ' || s[indices[i] + m] == '\0'))
        atomicAdd(d_c, 1);
}

int main() {
    char s[N], w[N];
    char *d_s, *d_w;

    int count = 0, numWords = 0, k = 0;
    int *d_c, *d_indices;

    float elapsedTime;

    printf("Enter a string : ");
    fgets(s, N, stdin);
    s[strcspn(s, "\n")] = 0;

    printf("Enter the word to find : ");
    fgets(w, N, stdin);
    w[strcspn(w, "\n")] = 0;

    numWords = 1;
    for (int i = 0; i < strlen(s); i++)
        if (s[i] == ' ')
            numWords++;

    int *wordIndices = (int *) malloc(numWords*sizeof(int));
    wordIndices[k++] = 0;
    for (int i=0; i<strlen(s); i++)
        if (s[i] == ' ')
            wordIndices[k++] = i+1;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaMalloc((void**)&d_s, strlen(s)*sizeof(char));
    cudaMalloc((void**)&d_w, strlen(w)*sizeof(char));
    cudaMalloc((void**)&d_indices, numWords*sizeof(int));
    cudaMalloc((void**)&d_c, sizeof(int));

    cudaMemcpy(d_c, &count, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_s, s, strlen(s), cudaMemcpyHostToDevice);
    cudaMemcpy(d_w, w, strlen(w), cudaMemcpyHostToDevice);
    cudaMemcpy(d_indices, wordIndices, numWords*sizeof(int), cudaMemcpyHostToDevice);

    cudaEventRecord(start, 0);

    CUDACount<<<1,numWords>>>(d_s, d_w, d_indices, d_c, strlen(s), strlen(w));
    
    cudaDeviceSynchronize();

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    cudaEventElapsedTime(&elapsedTime, start, stop);
    
    cudaMemcpy(&count, d_c, sizeof(int), cudaMemcpyDeviceToHost);
    
    printf("Total occurences of %s = %d\n", w, count);
    printf("Time Taken = %f\n",elapsedTime);
    
    cudaFree(d_s);
    cudaFree(d_c);
    cudaFree(d_w);
    cudaFree(d_indices);
    free(wordIndices);
    return 0;
}