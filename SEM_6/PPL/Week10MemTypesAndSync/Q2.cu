/*
2. Write a program in CUDA to improve the performance of 1D parallel convolution using constant Memory.

- convolution mask is read-only and shared across all threads => faster access through caching and broadcast.
- constant memory is better for read-only global reuse
*/

#include <stdio.h>
#include <cuda_runtime.h>

#define N 8
#define MASK_WIDTH 3
#define BLOCK_SIZE 4

__constant__ int d_mask[MASK_WIDTH];

__global__ void conv1D(int *input, int *output, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    int Pvalue = 0;

    if (i < n) {
        for (int j = 0; j < MASK_WIDTH; j++) {
            int idx = i - MASK_WIDTH/2 + j;
            if (idx >= 0 && idx < n)
                Pvalue += input[idx] * d_mask[j];
        }
        output[i] = Pvalue;
    }
}

int main() {
    int h_input[N], h_output[N];
    int h_mask[MASK_WIDTH];

    int *d_input, *d_output;

    printf("Enter %d elements of input array:\n", N);
    for (int i = 0; i < N; i++)
        scanf("%d", &h_input[i]);

    printf("Enter %d elements of mask:\n", MASK_WIDTH);
    for (int i = 0; i < MASK_WIDTH; i++)
        scanf("%d", &h_mask[i]);

    cudaMalloc((void**)&d_input, sizeof(int) * N);
    cudaMalloc((void**)&d_output, sizeof(int) * N);

    cudaMemcpy(d_input, h_input, sizeof(int) * N, cudaMemcpyHostToDevice);

    cudaMemcpyToSymbol(d_mask, h_mask, sizeof(int) * MASK_WIDTH);

    int gridSize = (N + BLOCK_SIZE - 1) / BLOCK_SIZE;
    conv1D<<<gridSize, BLOCK_SIZE>>>(d_input, d_output, N);

    cudaMemcpy(h_output, d_output, sizeof(int) * N, cudaMemcpyDeviceToHost);

    printf("\nOutput after convolution:\n");
    for (int i = 0; i < N; i++)
        printf("%d ", h_output[i]);

    printf("\n");

    cudaFree(d_input);
    cudaFree(d_output);

    return 0;
}