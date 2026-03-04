#include <iostream>
#include <random>
#include <chrono>

bool linear_search(int* arr, int n, int key) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == key) return true;
    }
    return false;
}

bool binary_search(int* arr, int n, int key) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == key) return true;
        if (arr[m] < key) l = m + 1;
        else r = m - 1;
    }
    return false;
}

int main() {
    int sizes[] = {500, 1000, 10000, 100000, 1000000,};
    std::cout << " " << std::endl;

    for (int n : sizes) {
        int* data = new int[n];
        for (int i = 0; i < n; ++i) data[i] = i * 2;

        auto start = std::chrono::steady_clock::now();
        for(int i = 0; i < 1000; ++i) linear_search(data, n, -1);
        auto end = std::chrono::steady_clock::now();
        double t_lin = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000.0 / 1000.0;

        start = std::chrono::steady_clock::now();
        for(int i = 0; i < 10000; ++i) binary_search(data, n, -1);
        end = std::chrono::steady_clock::now();
        double t_bin = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 10000.0 / 1000.0;

        std::cout << n << "," << t_lin << "," << t_bin << std::endl;
        delete[] data;
    }
    return 0;
}
