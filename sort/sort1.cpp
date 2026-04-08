#include <iostream>
#include <random>
#include <chrono>

void forward_step(unsigned arr[], unsigned const begin_idx, unsigned const end_idx) {
    for (unsigned i = begin_idx; i < end_idx; ++i) {
        if (arr[i] > arr[i + 1]) {
            unsigned temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }
}

void backward_step(unsigned arr[], unsigned const begin_idx, unsigned const end_idx) {
    for (unsigned i = end_idx; i > begin_idx; --i) {
        if (arr[i] < arr[i - 1]) {
            unsigned temp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = temp;
        }
    }
}

void shaker_sort(unsigned arr[], unsigned const begin_idx, unsigned const end_idx) {
    unsigned left = begin_idx;
    unsigned right = end_idx;
    while (left < right) {
        forward_step(arr, left, right);
        right--;
        if (left < right) {
            backward_step(arr, left, right);
            left++;
        }
    }
}

unsigned* generate_array(int N, std::default_random_engine& rng) {
    std::uniform_int_distribution<unsigned> dstr(0, 999);
    unsigned *ptr = new unsigned[N];
    for (int idx = 0; idx < N; ++idx) {
        ptr[idx] = dstr(rng);
    }
    return ptr;
}

void print_array(unsigned arr[], int N) {
    for (int i = 0; i < N; ++i) std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main() {
    unsigned seed = 10;
    std::default_random_engine rng(seed);
    int N = 10;

    unsigned* arr1 = generate_array(N, rng);
    print_array(arr1, N);
    forward_step(arr1, 0, N - 1);
    print_array(arr1, N);
    delete[] arr1;

    unsigned* arr2 = generate_array(N, rng);
    print_array(arr2, N);
    backward_step(arr2, 0, N - 1);
    print_array(arr2, N);
    delete[] arr2;

    unsigned* arr3 = generate_array(N, rng);
    print_array(arr3, N);
    shaker_sort(arr3, 0, N - 1);
    print_array(arr3, N);
    delete[] arr3;

    return 0;
}
