#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <string>

// Глобальный счетчик перестановок
unsigned long long total_swaps = 0;

// Функция обмена с подсчетом
void swap_elements(unsigned &a, unsigned &b) {
    unsigned temp = a;
    a = b;
    b = temp;
    total_swaps++;
}

// --- АЛГОРИТМЫ СОРТИРОВКИ ---

void shaker_sort(unsigned arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        for (int i = left; i < right; i++) 
            if (arr[i] > arr[i+1]) swap_elements(arr[i], arr[i+1]);
        right--;
        for (int i = right; i > left; i--) 
            if (arr[i-1] > arr[i]) swap_elements(arr[i-1], arr[i]);
        left++;
    }
}

void comb_sort(unsigned arr[], int n) {
    int gap = n;
    bool swapped = true;
    while (gap > 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        swapped = false;
        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                swap_elements(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void shell_sort_hibbard(unsigned arr[], int n) {
    int h = 1;
    while (h <= n) h = h * 2 + 1;
    while (h > 0) {
        for (int i = h; i < n; i++) {
            unsigned temp = arr[i];
            int j = i;
            while (j >= h && arr[j - h] > temp) {
                arr[j] = arr[j - h];
                j -= h;
                total_swaps++; // Сдвиг считаем за условную перестановку
            }
            arr[j] = temp;
        }
        h /= 2;
    }
}

void shell_sort_fibonacci(unsigned arr[], int n) {
    int fib[30]; 
    fib[0] = 1; fib[1] = 2;
    int k = 1;
    while (fib[k] < n) {
        k++;
        fib[k] = fib[k-1] + fib[k-2];
    }
    for (int idx = k - 1; idx >= 0; --idx) {
        int h = fib[idx];
        for (int i = h; i < n; i++) {
            unsigned temp = arr[i];
            int j = i;
            while (j >= h && arr[j - h] > temp) {
                arr[j] = arr[j - h];
                j -= h;
                total_swaps++;
            }
            arr[j] = temp;
        }
    }
}

// --- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ---

unsigned* generate_array(int n, std::default_random_engine& rng) {
    std::uniform_int_distribution<unsigned> dist(0, 10000);
    unsigned* arr = new unsigned[n];  // Исправлено: выделение массива из n элементов
    for (int i = 0; i < n; i++) arr[i] = dist(rng);
    return arr;
}

int main() {
    std::default_random_engine rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::ofstream out("results.csv");
    
    if (!out.is_open()) return 1;
    out << "Size,Algo,Time,Swaps\n";

    // Увеличенное количество тестов (20 точек)
    for (int n = 100; n <= 10000; n += 500) {
        unsigned* original = generate_array(n, rng);

        auto run_test = [&](void (*sort_func)(unsigned*, int), std::string name) {
            unsigned* copy = new unsigned[n];  // Исправлено: выделение массива из n элементов
            for (int i = 0; i < n; i++) copy[i] = original[i];
            
            total_swaps = 0;
            auto start = std::chrono::high_resolution_clock::now();
            sort_func(copy, n);
            auto end = std::chrono::high_resolution_clock::now();
            
            std::chrono::duration<double> duration = end - start;
            out << n << "," << name << "," << duration.count() << "," << total_swaps << "\n";
            
            delete[] copy;
        };

        run_test(shaker_sort, "Shaker");
        run_test(comb_sort, "Comb");
        run_test(shell_sort_hibbard, "Shell_Hibbard");
        run_test(shell_sort_fibonacci, "Shell_Fibonacci");

        delete[] original;
        std::cout << "Done for N = " << n << std::endl;
    }

    out.close();
    return 0;
}