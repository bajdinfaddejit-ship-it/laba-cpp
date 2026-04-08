#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

unsigned long long swaps = 0;

unsigned* generate_array(int N, std::default_random_engine& rng) {
    std::uniform_int_distribution<unsigned> dstr(0, 999);
    unsigned *ptr = new unsigned[N];
    for (int idx = 0; idx < N; ++idx) {
        ptr[idx] = dstr(rng);
    }
    return ptr;
}

void shell_step(unsigned arr[], int n, int gap) {
    for (int i = gap; i < n; i++) {
        unsigned temp = arr[i];
        int j = i;
        while (j >= gap && arr[j - gap] > temp) {
            arr[j] = arr[j - gap];
            j -= gap;
            swaps++; 
        }
        arr[j] = temp;
    }
}

void shell_classic(unsigned arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        shell_step(arr, n, gap);
    }
}

void shell_hibbard(unsigned arr[], int n) {
    int gaps[32];
    int count = 0;
    int h = 1;
    while (h <= n) {
        gaps[count++] = h;
        h = (h + 1) * 2 - 1;
    }
    for (int i = count - 1; i >= 0; i--) {
        shell_step(arr, n, gaps[i]);
    }
}

void shell_fibonacci(unsigned arr[], int n) {
    int gaps[45];
    int a = 1, b = 1;
    int count = 0;
    while (b <= n) {
        gaps[count++] = b;
        int next = a + b;
        a = b;
        b = next;
    }
    for (int i = count - 1; i >= 0; i--) {
        shell_step(arr, n, gaps[i]);
    }
}

int main() {
    unsigned const_seed = 42; 
    std::default_random_engine rng(const_seed);
    std::ofstream out("shell_results.csv");
    out << "Size,Algo,Time,Swaps\n";

    for (int n = 100; n <= 10000; n += 500) {
        unsigned* orig = generate_array(n, rng);

        // Test Classic
        {
            unsigned* copy = new unsigned[n];
            for (int i = 0; i < n; i++) copy[i] = orig[i];
            swaps = 0;
            auto start = std::chrono::high_resolution_clock::now();
            shell_classic(copy, n);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> d = end - start;
            out << n << ",Classic," << d.count() << "," << swaps << "\n";
            delete[] copy;
        }

        // Test Hibbard
        {
            unsigned* copy = new unsigned[n];
            for (int i = 0; i < n; i++) copy[i] = orig[i];
            swaps = 0;
            auto start = std::chrono::high_resolution_clock::now();
            shell_hibbard(copy, n);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> d = end - start;
            out << n << ",Hibbard," << d.count() << "," << swaps << "\n";
            delete[] copy;
        }

        // Test Fibonacci
        {
            unsigned* copy = new unsigned[n];
            for (int i = 0; i < n; i++) copy[i] = orig[i];
            swaps = 0;
            auto start = std::chrono::high_resolution_clock::now();
            shell_fibonacci(copy, n);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> d = end - start;
            out << n << ",Fibonacci," << d.count() << "," << swaps << "\n";
            delete[] copy;
        }

        delete[] orig;
        std::cout << "N = " << n << " processed." << std::endl;
    }
    out.close();
    return 0;
}
