/*
2. Write a program in CUDA to multiply two Matrices for the following specifications:
a. Each row of resultant matrix to be computed by one thread.
b. Each column of resultant matrix to be computed by one thread.
c. Each element of resultant matrix to be computed by one thread.*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>

__global__ void matMulRow(int *A, int *B, int *C, int hA, int wA, int wB) {
    int row = threadIdx.x;
    if (row < hA) {
        for (int col = 0; col < wB; col++) {
            int sum = 0;
            for (int k = 0; k < wA; k++)
                sum += A[row * wA + k] * B[k * wB + col];
            C[row * wB + col] = sum;
        }
    }
}

__global__ void matMulCol(int *A, int *B, int *C, int hA, int wA, int wB) {
    int col = threadIdx.x;

    if (col < wB) {
        for (int row = 0; row < hA; row++) {
            int sum = 0;
            for (int k = 0; k < wA; k++)
                sum += A[row * wA + k] * B[k * wB + col];
            C[row * wB + col] = sum;
        }
    }
}

__global__ void matMulEle(int *A, int *B, int *C, int hA, int wA, int wB) {
    int row = threadIdx.y;
    int col = threadIdx.x;

    if (row < hA && col < wB) {
        int sum = 0;
        for (int k = 0; k < wA; k++)
            sum += A[row * wA + k] * B[k * wB + col];
        C[row * wB + col] = sum;
    }
}

int main(void) {
    int m, n, p;

    printf("Enter rows and cols of A (m n): ");
    scanf("%d %d", &m, &n);

    printf("Enter cols of B (p): ");
    scanf("%d", &p);

    int *A = (int*)malloc(m * n * sizeof(int));
    int *B = (int*)malloc(n * p * sizeof(int));
    int *C = (int*)malloc(m * p * sizeof(int));
    
    printf("Enter matrix A:\n");
    for (int i = 0; i < m * n; i++)
        scanf("%d", &A[i]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < n * p; i++)
        scanf("%d", &B[i]);
    
    int *d_A, *d_B, *d_C;

    cudaMalloc((void**)&d_A, m * n * sizeof(int));
    cudaMalloc((void**)&d_B, n * p * sizeof(int));
    cudaMalloc((void**)&d_C, m * p * sizeof(int));

    cudaMemcpy(d_A, A, m * n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, n * p * sizeof(int), cudaMemcpyHostToDevice);

    float elapsedTimeRow, elapsedTimeCol, elapsedTimeEle;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Row
    cudaEventRecord(start, 0);
    matMulRow<<<1, m>>>(d_A, d_B, d_C, m, n, p);
    // cudaDeviceSynchronize(); //not needed as we are doing cudaEventSynchronize(stop)
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsedTimeRow, start, stop);

    // Col
    cudaEventRecord(start, 0);
    matMulCol<<<1, p>>>(d_A, d_B, d_C, m, n, p);
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsedTimeCol, start, stop);

    // Ele
    dim3 threads(p, m);
    cudaEventRecord(start, 0);
    matMulEle<<<1, threads>>>(d_A, d_B, d_C, m, n, p);
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsedTimeEle, start, stop);

    cudaMemcpy(C, d_C, m * p * sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nResult matrix C:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++)
            printf("%d ", C[i * p + j]);
        printf("\n");
    }

    printf("\n Row : %f", elapsedTimeRow);
    printf("\n Col : %f", elapsedTimeCol);
    printf("\n Ele : %f \n", elapsedTimeEle);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(A);
    free(B);
    free(C);

    return 0;
}