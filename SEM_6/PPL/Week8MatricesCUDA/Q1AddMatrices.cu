/*
1. Write a program in CUDA to add two Matrices for the following specifications:
a. Each row of resultant matrix to be computed by one thread.
b. Each column of resultant matrix to be computed by one thread.
c. Each element of resultant matrix to be computed by one thread.
*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>

__global__ void matSumRow(int *A, int *B, int *C, int m, int n) {
    int row = threadIdx.x;

    if (row < m)
        for (int col = 0; col < n; col++)
            C[row * n + col] = A[row * n + col] + B[row * n + col];
}

__global__ void matSumCol(int *A, int *B, int *C, int m, int n) {
    int col = threadIdx.x;

    if (col < n)
        for (int row = 0; row < m; row++)
            C[row * n + col] = A[row * n + col] + B[row * n + col];
}

__global__ void matSumEle(int *A, int *B, int *C, int m, int n) {
    int row = threadIdx.y;
    int col = threadIdx.x;

    if (row < m && col < n)
        C[row * n + col] = A[row * n + col] + B[row * n + col];
}

int main(void) {
    int m, n, size;

    printf("Enter rows and cols of A (m n): ");
    scanf("%d %d", &m, &n);

    size = m*n*sizeof(int);

    int *A = (int*)malloc(size);
    int *B = (int*)malloc(size);
    int *C = (int*)malloc(size);
    
    printf("Enter matrix A:\n");
    for (int i = 0; i < m * n; i++)
        scanf("%d", &A[i]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < n * n; i++)
        scanf("%d", &B[i]);
    
    int *d_A, *d_B, *d_C;

    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);


    // a) Row-wise
    matSumRow<<<1, m>>>(d_A, d_B, d_C, m, n);

    // b) Column-wise
    // matSumCol<<<1, n>>>(d_A, d_B, d_C, m, n);

    // c) Element-wise
    // dim3 threads(n, m);
    // matSumEle<<<1, threads>>>(d_A, d_B, d_C, m, n);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    printf("\nResult matrix C:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i * n + j]);
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(A);
    free(B);
    free(C);

    return 0;
}
