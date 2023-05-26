%%cu
#include <stdio.h>
#include <stdlib.h>

__global__ void add(int *arr1_gpu, int *arr2_gpu, int *res_gpu, int size)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    if (index < size)
    {
        res_gpu[index] = arr1_gpu[index] + arr2_gpu[index];
    }
}

int main()
{
    int size = 10;
    // scanf("%d", &size);

    // declare arrays
    int *arr1_cpu = (int *)malloc(size * sizeof(int));
    int *arr2_cpu = (int *)malloc(size * sizeof(int));
    int *res_cpu = (int *)malloc(size * sizeof(int));

    // fill them with values
    for (int i = 0; i < size; i++)
    {
        arr1_cpu[i] = rand() % 100;
        arr2_cpu[i] = rand() % 100;
    }

    int *arr1_gpu, *arr2_gpu, *res_gpu;

    // allocate memory for arrays on GPU
    cudaMalloc((void **)&arr1_gpu, size * sizeof(int));
    cudaMalloc((void **)&arr2_gpu, size * sizeof(int));
    cudaMalloc((void **)&res_gpu, size * sizeof(int));

    // copy data from cpu to gpu
    cudaMemcpy(arr1_gpu, arr1_cpu, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(arr2_gpu, arr2_cpu, size * sizeof(int), cudaMemcpyHostToDevice);

    // add
    int blocksize = 256;
    int gridsize = (size + blocksize - 1) / blocksize;

    add<<<gridsize, blocksize>>>(arr1_gpu, arr2_gpu, res_gpu, size);

    // copy result back to cpu
    cudaMemcpy(res_cpu, res_gpu, size * sizeof(int), cudaMemcpyDeviceToHost);

    // print result
    for (int i = 0; i < size; i++)
    {
        printf("%d + %d = %d\n", arr1_cpu[i], arr2_cpu[i], res_cpu[i]);
    }

    // free memory
    cudaFree(arr1_gpu);
    cudaFree(arr2_gpu);
    cudaFree(res_gpu);

    free(arr1_cpu);
    free(arr2_cpu);
    free(res_cpu);

    return 0;
}


// CUDA (Compute Unified Device Architecture) is a parallel computing platform and programming model created by NVIDIA. It allows developers to utilize the power of NVIDIA graphics processing units (GPUs) for general-purpose computing tasks, in addition to their traditional graphics rendering capabilities.

// CUDA provides a framework and set of tools for writing high-performance parallel programs that can execute on NVIDIA GPUs. It includes a programming language called CUDA C/C++ that extends the C/C++ programming language with GPU-specific primitives and syntax. CUDA C/C++ allows developers to write code that can be executed in parallel on the GPU, taking advantage of the massive parallelism offered by modern GPUs.

// By using CUDA, developers can harness the computational power of GPUs for a wide range of applications, including scientific simulations, data analytics, image and video processing, deep learning, and more. CUDA-enabled GPUs have hundreds or even thousands of cores that can execute computations in parallel, making them well-suited for tasks that can be broken down into smaller, independent parts.

// In addition to CUDA C/C++, NVIDIA provides CUDA libraries that offer optimized implementations of common algorithms and functions, such as linear algebra, signal processing, and image manipulation. These libraries help simplify the development process and enable developers to achieve high performance with minimal effort.

// Overall, CUDA has become a popular platform for GPU computing, enabling developers to leverage the immense computational power of GPUs to accelerate a wide range of applications.