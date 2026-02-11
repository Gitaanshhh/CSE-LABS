# CUDA

## Host
Host : CPU
Host Memory : CPU Memory
Runs Serial Code

## Device
Device : GPU
Device Memory : GPU Memory
Runs Parallel code

1. Copy data from Host to Device Mem
2. Load Device Program and execute
3. Copy result from Device to Host Mem

## Important Terms

### Kernel :
- A Function that runs on the GPU.
- Defines the parallel work to execute.
- One kernel launch creates thousands of threads on the GPU.
- Launched like :
```myKernel<<<numBlocks, threadsPerBlock>>>();```

### Thread :
- The smallest execution unit.
- Works on different data and has its own registers and local memory.
- Distributed by CUDA runtime.
- A single path of execution.
- There can be multiple threads in a program.
- Indexing
```
threadIdx.x
threadIdx.y
threadIdx.z
```

### Block : 
- User defined group of 1 to 512 threads.
- Threads inside a block Run on the same Streaming Multiprocessor (SM), can share fast shared memeory and synchronize.
- Assigned to SMs and run independently.
- Identified by blockIdx.
- Access
```
blockIdx.x
blockDim.x
```
- Global Thread Index (Can be used to iterate an array, etc.)
```int globalId = blockIdx.x * blockDim.x + threadIdx.x;```


### Grid :
- Collection of 1 or more blocks.
- A Grid is created for each CUDA kernel function.
- Access
```gridDim.x```

### Streaming Multiprocessor (SM)
- Physical hardware unit inside the GPU that actually executes threads.
- A GPU contains many SMs.

### Warp
- Hardware scheduling unit

### Parallel at different levels:
- Multiple SMs execute blocks simultaneously.
- Within an SM, multiple warps execute concurrently.
- Within a warp, 32 threads execute in lockstep (SIMT).
