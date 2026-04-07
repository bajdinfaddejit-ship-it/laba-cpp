#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

unsigned long long swaps = 0;

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
    int gaps[32]; // Статический массив для шагов
    int count = 0;
    int h = 1;
    // Генерируем 2^i - 1: 1, 3, 7, 15...
    while (h <= n) {
        gaps[count++] = h;
        h = (h + 1) * 2 - 1;
    }
    for (int i = count - 1; i >= 0; i--) {
        shell_step(arr, n, gaps[i]);
    }
}

void shell_fibonacci(unsigned arr[], int n) {
    int gaps[45]; // Числа Фибоначчи до 2^31
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
    std::ofstream out("shell_results.csv");
    out << "Size,Algo,Time,Swaps\n";
    
    std::default_random_engine rng(42);
    std::uniform_int_distribution<unsigned> dist(0, 100000);

    for (int n = 100; n <= 10000; n += 500) {
        unsigned* orig = new unsigned[n];
        for (int i = 0; i < n; i++) orig[i] = dist(rng);

        // Тест Classic
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

        // Тест Hibbard
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

        // Тест Fibonacci
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
    }
    out.close();
    return 0;
}
