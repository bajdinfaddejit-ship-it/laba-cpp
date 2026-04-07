#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

unsigned long long current_swaps = 0;

void swap(unsigned &a, unsigned &b) {
    unsigned temp = a;
    a = b;
    b = temp;
    current_swaps++;
}

bool check_and_swap_with_gap(unsigned arr[], unsigned n, unsigned gap) {
    bool swapped = false;
    for (unsigned i = 0; i + gap < n; ++i) {
        if (arr[i] > arr[i + gap]) {
            swap(arr[i], arr[i + gap]);
            swapped = true;
        }
    }
    return swapped;
}

void comb_sort(unsigned arr[], unsigned n) {
    unsigned gap = n;
    const double shrink = 1.3;
    bool swapped = true;
    while (gap > 1 || swapped) {
        gap = (unsigned)(gap / shrink);
        if (gap < 1) gap = 1;
        swapped = check_and_swap_with_gap(arr, n, gap);
    }
}

int main() {
    std::default_random_engine rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<unsigned> dstr(0, 10000);
    std::ofstream out("comb_sort_data.csv");

    out << "Size,Time,Swaps\n";

    for (int n = 100; n <= 10000; n += 500) {
        unsigned* arr = new unsigned[n];
        for (int i = 0; i < n; i++) arr[i] = dstr(rng);

        current_swaps = 0;
        auto start = std::chrono::high_resolution_clock::now();
        comb_sort(arr, n);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        out << n << "," << duration.count() << "," << current_swaps << "\n";

        delete[] arr;
        std::cout << "N = " << n << " done.\n";
    }

    out.close();
    return 0;
}
