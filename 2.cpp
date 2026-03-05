#include <iostream>
#include <chrono>
#include <random>

unsigned* generate_array(int N, std::default_random_engine& rng) {
    std::uniform_int_distribution<unsigned> dstr(0, 999);
    unsigned *ptr = new unsigned[N];
    for (int idx = 0; idx < N; ++idx) {
        ptr[idx] = dstr(rng);
    }
    return ptr;
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

bool sum_brute(unsigned* arr, int n, int target) {
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (arr[i] + arr[j] == target) return true;
    return false;
}

bool sum_fast(unsigned* arr, int n, int target) {
    int l = 0, r = n - 1;
    while (l < r) {
        int s = arr[l] + arr[r];
        if (s == target) return true;
        if (s < target) l++; else r--;
    }
    return false;
}

int main() {
    int sizes[] = {500, 1000, 5000, 10000, 50000, 100000, 150000};
    
    unsigned seed = 12345;
    std::default_random_engine rng(seed);
    
    std::cout << "Сид: " << seed << std::endl;
    std::cout << "N,BruteForce(мкс),Fast(мкс)" << std::endl;

    for (int n : sizes) {
        unsigned* data = generate_array(n, rng);
        
        unsigned* sorted_data = new unsigned[n];
        for (int i = 0; i < n; ++i) {
            sorted_data[i] = data[i];
        }
        insertion_sort(sorted_data, n);
        
        std::uniform_int_distribution<int> target_dist(10, 2000);
        int target = target_dist(rng);

        auto start = std::chrono::steady_clock::now();
        sum_brute(data, n, target);
        auto end = std::chrono::steady_clock::now();
        long long t_brute = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        start = std::chrono::steady_clock::now();
        for(int i = 0; i < 1000; i++) sum_fast(sorted_data, n, target);
        end = std::chrono::steady_clock::now();
        double t_fast = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;

        std::cout << n << "," << t_brute << "," << t_fast << std::endl;
        
        delete[] data;
        delete[] sorted_data;
    }
    return 0;
}