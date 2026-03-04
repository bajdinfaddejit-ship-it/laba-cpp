#include <iostream>
#include <chrono>

bool sum_brute(int* arr, int n, int target) {
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (arr[i] + arr[j] == target) return true;
    return false;
}

bool sum_fast(int* arr, int n, int target) {
    int l = 0, r = n - 1;
    while (l < r) {
        int s = arr[l] + arr[r];
        if (s == target) return true;
        if (s < target) l++; else r--;
    }
    return false;
}

int main() {
    int sizes[] = {500, 1000,5000, 10000,50000, 100000, 150000};
    std::cout << " " << std::endl;

    for (int n : sizes) {
        int* data = new int[n];
        for (int i = 0; i < n; ++i) data[i] = i;

        auto start = std::chrono::steady_clock::now();
        sum_brute(data, n, -1);
        auto end = std::chrono::steady_clock::now();
        long long t_brute = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        start = std::chrono::steady_clock::now();
        for(int i=0; i<1000; i++) sum_fast(data, n, -1);
        end = std::chrono::steady_clock::now();
        double t_fast = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;

        std::cout << n << "," << t_brute << "," << t_fast << std::endl;
        delete[] data;
    }
    return 0;
}

