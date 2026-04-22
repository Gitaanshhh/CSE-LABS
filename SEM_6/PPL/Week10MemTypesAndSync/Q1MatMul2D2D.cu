/*
1. Write a program in CUDA to perform matrix multiplication using 2D Grid and 2D Block.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define WIDTH 4
#define BLOCK_WIDTH 2

__global__ void MatMul(int *a, int *b, int *c) {
    
    int bx = blockIdx.x;
    int by = blockIdx.y;
    int tx = threadIdx.x;
    int ty = threadIdx.y;

    int Row = by * BLOCK_WIDTH + ty;
    int Col = bx * BLOCK_WIDTH + tx;

    int Pvalue = 0;

    for (int k = 0; k < WIDTH; k++)
        Pvalue += a[Row * WIDTH + k] * b[k * WIDTH + Col];
    c[Row * WIDTH + Col] = Pvalue;
}

int main() {
    int *matA, *matB, *matProd;
    int *da, *db, *dc;

    printf("\n== Enter elements of Matrix A (4x4) ==\n");
    matA = (int*)malloc(sizeof(int) * WIDTH * WIDTH);
    for(int i = 0; i < WIDTH * WIDTH; i++)
        scanf("%d", &matA[i]);

    printf("\n== Enter elements of Matrix B (4x4) ==\n");
    matB = (int*)malloc(sizeof(int) * WIDTH * WIDTH);
    for(int i = 0; i < WIDTH * WIDTH; i++)
        scanf("%d", &matB[i]);

    matProd = (int*)malloc(sizeof(int) * WIDTH * WIDTH);

    cudaMalloc((void**)&da, sizeof(int) * WIDTH * WIDTH);
    cudaMalloc((void**)&db, sizeof(int) * WIDTH * WIDTH);
    cudaMalloc((void**)&dc, sizeof(int) * WIDTH * WIDTH);

    cudaMemcpy(da, matA, sizeof(int) * WIDTH * WIDTH, cudaMemcpyHostToDevice);
    cudaMemcpy(db, matB, sizeof(int) * WIDTH * WIDTH, cudaMemcpyHostToDevice);

    int NumBlocks = WIDTH / BLOCK_WIDTH;

    dim3 grid_conf(NumBlocks, NumBlocks);
    dim3 block_conf(BLOCK_WIDTH, BLOCK_WIDTH);

    MatMul<<<grid_conf, block_conf>>>(da, db, dc);

    cudaMemcpy(matProd, dc, sizeof(int) * WIDTH * WIDTH, cudaMemcpyDeviceToHost);

    printf("\n-=Result of Matrix Multiplication=-\n");
    printf("----------\n");

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < WIDTH; j++)
            printf("%6d ", matProd[i * WIDTH + j]);
        printf("\n");
    }

    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);

    free(matA);
    free(matB);
    free(matProd);

    return 0;
}