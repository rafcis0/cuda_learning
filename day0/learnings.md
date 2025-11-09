1. CPU programs work sequentially. So in this case add.cpp grabs and does one addition at a time (obviously this can be parallelized or hyperthreaded, but let's keep it dumb atm)

2. GPUs do as many iterations as threads at a time in parallel. So in this case add_gpu.cpp grabs and does the three additions at the same time.

3. a kernel is a function that runs on the GPU. In the case of add_gpu.cpp it is the __global__ function

3.5 Host --> CPU // Device --> GPU

4. What about the other stuff?

    - cudaMalloc(&d_x, N * sizeof(float)) 
        - This maps N logical threads in the  GPU, and redirects the pointer d_x to the space in the GPU instead of the CPU

    - cudaMemcpy(d_x, x, N * sizeof(float), cudaMemcpyHostToDevice)
        - cudaMalloc allocated empty space with the pointer d_x
        - Now what cudaMemcpy does is it copies the N * sizeof(float) bytes from x (on the CPU) to d_x (on the GPU)
        - While the kernel is async (see below), this operation is blocking... so it waits until completed to continue

    - add<<<1, N>>>(d_x, d_y, N)
        - this is the part where it says to run the function 'add' on 1 blocks and N threads per block
        - It sends the kernel 'add' (defined by __global__) to the GPU, allocates those N threads to the hardware, and each thread runs a copy of that kernel in parallel
        - Note that this is asynchronous... so the CPU sends to GPU and continues doing its stuff. Somtimes we have cudaDeviceSynchronize() which ensures the GPU finishes before sending back to the CPU
        - kernel_name<<<numBlocks, threadsPerBlock>>>(arguments...)

    - int i = threadIdx.x
        - This is the index of the thread within the block (0,1,2 in the example of add_gpu)
        - inside the kernel we also have 'if (i < n)' this is so that extra threads don't jsut spin up empty

    - Other than threadIdx we could have:
        - blockIdx.x --> Index of the block within the grid (In this example always 0, since blockIdx.x = 0)
        - blockDim.x --> is the number of threads per block (3, duh)
        - gridDim.x --> the number of blocks in the grid

    - cudaMemcpy(y, d_y, N * sizeof(float), cudaMemcpyDeviceToHost)
        - Basically to bring back into y (in the cpu) the data pointed at by d_y (in the GPU)

    - cudaFree(d_x)
        - kinda obvious... it's to free up the memory in the GPU

 
Notes to learn more:
    - We start with x but I read there can be y and z in the threadIdx... what's that about?
    