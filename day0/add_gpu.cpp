#include <iostream>
#include <cuda_runtime.h>

// let's now try it in cuda
__global__
void add(float *x, float *y, int n) {
    int i = threadIdx.x;
    if (i < n)
        y[i] = x[i] + y[i];
}

int main() {
    //same as earlier
  float x[] = {1, 2, 3};
  float y[] = {4, 5, 6};
  int N = sizeof(x) / sizeof(x[0]);
  
  // Allocate device memory
  float *d_x, *d_y;
  cudaMalloc(&d_x, N * sizeof(float));
  cudaMalloc(&d_y, N * sizeof(float));
  
  // Copy data from host to device
  cudaMemcpy(d_x, x, N * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(d_y, y, N * sizeof(float), cudaMemcpyHostToDevice);
  
  // Launch kernel with 1 block and N threads
  add<<<1, N>>>(d_x, d_y, N);
  
  // Copy results back from device to host
  cudaMemcpy(y, d_y, N * sizeof(float), cudaMemcpyDeviceToHost);
  
  // Free device memory
  cudaFree(d_x);
  cudaFree(d_y);
  
  // print out the results
  for (int i = 0; i < N; i++) {
    std::cout << y[i];
    if (i < N - 1) std::cout << ", ";
  }
  std::cout << std::endl;
  
  return 0;
}
