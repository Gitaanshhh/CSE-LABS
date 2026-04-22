/*
3. Write a CUDA program that reads a matrix A of size MXN and produce an output matrix B of same size such that it replaces all the non-border elements(numbers in bold) of A with its equivalent 1’s complement and remaining elements same as matrix A.
*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>

__device__ int onesComplementBinary(int num) {
    int bin[32], n = 0;

    while (num > 0) {
        bin[n++] = num % 2;
        num /= 2;
    }

    for (int i = 0; i < n; i++)
        bin[i] = 1 - bin[i];

    int result = 0, place = 1;
    for (int i = 0; i < n; i++) {
        result += bin[i] * place;
        place *= 10;
    }

    return result;
}

__global__ void transform(int *A, int *B, int rows, int cols) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < rows && col < cols) {

        int idx = row * cols + col;

        if (row == 0 || row == rows - 1 || col == 0 || col == cols - 1)
            B[idx] = A[idx];
        else
            B[idx] = onesComplementBinary(A[idx]);
    }
}

int main() {
    int rows, cols;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    int size = rows * cols * sizeof(int);

    int *A = (int*)malloc(size);
    int *B = (int*)malloc(size);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows * cols; i++)
        scanf("%d", &A[i]);

    int *d_A, *d_B;

    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);

    dim3 threads(16, 16);
    dim3 blocks((cols + 15) / 16, (rows + 15) / 16);

    transform<<<blocks, threads>>>(d_A, d_B, rows, cols);

    cudaMemcpy(B, d_B, size, cudaMemcpyDeviceToHost);

    printf("\nResult matrix B:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", B[i * cols + j]);
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);
    free(A);
    free(B);

    return 0;
}