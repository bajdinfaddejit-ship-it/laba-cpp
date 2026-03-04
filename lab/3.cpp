#include <iostream>
#include <chrono>
#include <random>

int searchA(int* arr, int size, int key) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            if (i != 0) {
                int temp = arr[i];
                arr[i] = arr[0];
                arr[0] = temp;
            }
            return i;
        }
    }
    return -1;
}

int searchB(int* arr, int size, int key) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            if (i != 0) {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
            }
            return i;
        }
    }
    return -1;
}

int searchC(int* arr, int* counts, int size, int key) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            counts[i]++;
            if (i > 0 && counts[i] > counts[i - 1]) {
                int tempArr = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = tempArr;
                int tempCnt = counts[i];
                counts[i] = counts[i - 1];
                counts[i - 1] = tempCnt;
            }
            return i;
        }
    }
    return -1;
}

int main() {
    int sizes[] = {100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000};
    int numSizes = 10;
    
    unsigned seed = 12345;
    std::default_random_engine rng(seed);
    
    std::cout << "N\tStrategyA\tStrategyB\tStrategyC\n";
    
    for (int s = 0; s < numSizes; ++s) {
        int N = sizes[s];
        
        int* arr = new int[N];
        int* arrA = new int[N];
        int* arrB = new int[N];
        int* arrC = new int[N];
        int* countsC = new int[N]();

        for (int i = 0; i < N; ++i) {
            arr[i] = i;
        }
        
        for (int i = 0; i < N; ++i) {
            arrA[i] = arr[i];
            arrB[i] = arr[i];
            arrC[i] = arr[i];
        }
        
        int hotSize = N * 0.2;
        int* hot = new int[hotSize];
        for (int i = 0; i < hotSize; ++i) {
            hot[i] = i;
        }
        
        std::uniform_int_distribution<int> distUniform(0, N - 1);
        std::uniform_int_distribution<int> distHot(0, hotSize - 1);
        
        const int repeats = 100000;
        
        auto begin = std::chrono::steady_clock::now();
        for (int r = 0; r < repeats; ++r) {
            int key;
            if (r % 5 == 0) {
                key = N + r;
            } else {
                if (r < repeats * 0.8) {
                    key = hot[distHot(rng)];
                } else {
                    key = distUniform(rng);
                }
            }
            searchA(arrA, N, key);
        }
        auto end = std::chrono::steady_clock::now();
        auto timeA = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        begin = std::chrono::steady_clock::now();
        for (int r = 0; r < repeats; ++r) {
            int key;
            if (r % 5 == 0) {
                key = N + r;
            } else {
                if (r < repeats * 0.8) {
                    key = hot[distHot(rng)];
                } else {
                    key = distUniform(rng);
                }
            }
            searchB(arrB, N, key);
        }
        end = std::chrono::steady_clock::now();
        auto timeB = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        for (int i = 0; i < N; ++i) countsC[i] = 0;
        
        begin = std::chrono::steady_clock::now();
        for (int r = 0; r < repeats; ++r) {
            int key;
            if (r % 5 == 0) {
                key = N + r;
            } else {
                if (r < repeats * 0.8) {
                    key = hot[distHot(rng)];
                } else {
                    key = distUniform(rng);
                }
            }
            searchC(arrC, countsC, N, key);
        }
        end = std::chrono::steady_clock::now();
        auto timeC = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        
        std::cout << N << "\t" << timeA << "\t\t" << timeB << "\t\t" << timeC << "\n";
        
        delete[] arr;
        delete[] arrA;
        delete[] arrB;
        delete[] arrC;
        delete[] countsC;
        delete[] hot;
    }
    
    return 0;
}