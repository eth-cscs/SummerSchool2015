#include <iostream>

#include <cuda.h>

#include "util.h"

// host implementation of dot product
double dot_host(const double *x, const double* y, int n) {
    double sum = 0;
    for(auto i=0; i<n; ++i) {
        sum += x[i]*y[i];
    }
    return sum;
}

// for handling non-powers-of-two we need some helpers
// for detecting power of two and rounding up to the next
// power of two
__device__
bool is_power_of_two(int n) {
    return (n & (n - 1)) == 0;
}

__device__
int next_power_of_two(int n) {
    if (n < 0) {
        return 0;
    }
    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n+1;
}

// solution for arbitrary n<=1024
__global__
void dot_gpu_kernel(const double *x, const double* y, double *result, int n) {
    extern __shared__ double buffer[];

    int idx = threadIdx.x;

    // all threads set buffer to zero, regardless of whether
    // they will participate in the reduction
    // this ensures that the binary reduction step works
    buffer[idx] = 0.;
    __syncthreads();

    if(idx<n) {
        buffer[idx] = x[idx]*y[idx];
        __syncthreads();

        if(!is_power_of_two(n)) {
            n = next_power_of_two(n);
        }
        auto m = n/2;
        while(m) {
            __syncthreads();
            if(idx<m) {
                buffer[idx] += buffer[idx+m];
            }

            m /= 2;
        }

        if(idx==0) {
            result[0] = buffer[0];
        }
    }
}

double dot_gpu(const double *x, const double* y, int n) {
    static double* result = malloc_device<double>(1);
    double r;
    dot_gpu_kernel<<<1, 1024, sizeof(double)*1024>>>(x, y, result, n);
    copy_to_host<double>(result, &r, 1);
    return r;
}

int main(int argc, char** argv) {
    size_t n  = read_arg(argc, argv, 1, 4);

    auto size_in_bytes = n * sizeof(double);

    std::cout << "dot product CUDA of length n = " << n
              << " : " << size_in_bytes/(1024.*1024.) << "MB"
              << std::endl;

    cuInit(0);

    auto x_h = malloc_host<double>(n, 2.);
    auto y_h = malloc_host<double>(n);
    for(auto i=0; i<n; ++i) {
        y_h[i] = rand()%10;
    }

    auto x_d = malloc_device<double>(n);
    auto y_d = malloc_device<double>(n);

    // copy initial conditions to device
    copy_to_device<double>(x_h, x_d, n);
    copy_to_device<double>(y_h, y_d, n);

    auto result   = dot_gpu(x_d, y_d, n);
    auto expected = dot_host(x_h, y_h, n);
    std::cout << "expected " << expected << " got " << result << std::endl;

    return 0;
}

