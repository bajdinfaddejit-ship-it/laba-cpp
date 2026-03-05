#include <iostream>
#include <random>
#include <chrono>

unsigned* generate_array(int N, std::default_random_engine& rng) {
    std::uniform_int_distribution<unsigned> dstr(0, 999);
    unsigned *ptr = new unsigned[N];
    for (int idx = 0; idx < N; ++idx) {
        ptr[idx] = dstr(rng);
    }
    return ptr;
}

bool linear_search(unsigned* arr, int n, unsigned key) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == key) return true;
    }
    return false;
}

bool binary_search(unsigned* arr, int n, unsigned key) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == key) return true;
        if (arr[m] < key) l = m + 1;
        else r = m - 1;
    }
    return false;
}

void insertion_sort(unsigned* arr, int n) {
    for (int i = 1; i < n; ++i) {
        unsigned key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int sizes[] = {500, 1000, 10000, 100000, 200000};
    
    unsigned seed = 12345;
    std::default_random_engine rng(seed);

    std::cout << "Сид: " << seed << std::endl;
    std::cout << "N,LinearSearch(мкс),BinarySearch(мкс)" << std::endl;

    for (int n : sizes) {
        unsigned* data = generate_array(n, rng);
        unsigned* sorted_data = new unsigned[n];
        for (int i = 0; i < n; ++i) {
            sorted_data[i] = data[i];
        }
        insertion_sort(sorted_data, n);

        auto start = std::chrono::steady_clock::now();
        for(int i = 0; i < 1000; ++i) linear_search(data, n, 1000);
        auto end = std::chrono::steady_clock::now();
        double t_lin = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000.0 / 1000.0;

        start = std::chrono::steady_clock::now();
        for(int i = 0; i < 10000; ++i) binary_search(sorted_data, n, 1000);
        end = std::chrono::steady_clock::now();
        double t_bin = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 10000.0 / 1000.0;

        std::cout << n << "," << t_lin << "," << t_bin << std::endl;
        
        delete[] data;
        delete[] sorted_data;
    }
    return 0;
}