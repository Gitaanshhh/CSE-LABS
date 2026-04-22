/*
3. Write a program in CUDA to perform tiled 1D convolution operation on the input array N of size width using the mask array, M of size mask width, to produce the resultant array P of size width

- Tiled convolution uses shared memory to load input segments with halo regions, reducing global memory access and improving performance.
- Each block loads -> Its own TILE_SIZE elements and extra halo elements => avoids repeated global memory access
*/

#include <stdio.h>
#include <cuda_runtime.h>

#define WIDTH 8
#define MASK_WIDTH 3
#define TILE_SIZE 4

__global__ void tiledConv1D(int *N, int *M, int *P, int width) {
    
    __shared__ int Ns[TILE_SIZE + MASK_WIDTH - 1];  // shared memory with halo -> extra space For halo elements (neighbors needed for convolution)

    int tx = threadIdx.x;
    int bx = blockIdx.x;
    
    int start = bx * TILE_SIZE;    //global blockId
    int i = start + tx;            //global threadInd 

    int halo = MASK_WIDTH / 2;

    if (i < width)
        Ns[tx + halo] = N[i];
    else
        Ns[tx + halo] = 0;

    if (tx < halo) {
        int leftIdx = i - halo;
        Ns[tx] = (leftIdx >= 0) ? N[leftIdx] : 0;
    }

    if (tx < halo) {
        int rightIdx = i + TILE_SIZE;
        Ns[tx + TILE_SIZE + halo] = (rightIdx < width) ? N[rightIdx] : 0;
    }

    __syncthreads();

    if (i < width) {
        int Pvalue = 0;
        for (int j = 0; j < MASK_WIDTH; j++)
            Pvalue += Ns[tx + j] * M[j];
        P[i] = Pvalue;
    }
}

int main() {
    int h_N[WIDTH], h_M[MASK_WIDTH], h_P[WIDTH];
    int *d_N, *d_M, *d_P;

    printf("Enter %d elements of input array:\n", WIDTH);
    for (int i = 0; i < WIDTH; i++)
        scanf("%d", &h_N[i]);

    printf("Enter %d elements of mask:\n", MASK_WIDTH);
    for (int i = 0; i < MASK_WIDTH; i++)
        scanf("%d", &h_M[i]);

    cudaMalloc((void**)&d_N, sizeof(int) * WIDTH);
    cudaMalloc((void**)&d_M, sizeof(int) * MASK_WIDTH);
    cudaMalloc((void**)&d_P, sizeof(int) * WIDTH);

    cudaMemcpy(d_N, h_N, sizeof(int) * WIDTH, cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, h_M, sizeof(int) * MASK_WIDTH, cudaMemcpyHostToDevice);

    int gridSize = (WIDTH + TILE_SIZE - 1) / TILE_SIZE;

    tiledConv1D<<<gridSize, TILE_SIZE>>>(d_N, d_M, d_P, WIDTH);

    cudaMemcpy(h_P, d_P, sizeof(int) * WIDTH, cudaMemcpyDeviceToHost);

    printf("\nOutput after tiled convolution:\n");
    for (int i = 0; i < WIDTH; i++)
        printf("%d ", h_P[i]);

    printf("\n");

    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);

    return 0;
}
