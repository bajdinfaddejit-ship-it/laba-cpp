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

int searchA(unsigned* arr, int size, unsigned key) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            if (i != 0) {
                unsigned temp = arr[i];
                arr[i] = arr[0];
                arr[0] = temp;
            }
            return i;
        }
    }
    return -1;
}

int searchB(unsigned* arr, int size, unsigned key) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            if (i != 0) {
                unsigned temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
            }
            return i;
        }
    }
    return -1;
}

int searchC(unsigned* arr, int* counts, int size, unsigned key) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            counts[i]++;
            
            if (i > 0 && counts[i] > counts[i - 1]) {
                unsigned tempArr = arr[i];
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
    
    std::cout << "===== ЗАДАНИЕ 3: АДАПТИВНЫЙ ПОИСК =====" << std::endl;
    std::cout << "Сид: " << seed << std::endl;
    std::cout << "Исследуются три стратегии при неравномерном распределении запросов" << std::endl;
    std::cout << "(80% запросов к 20% 'горячих' элементов, 20% неудачных поисков)" << std::endl;
    std::cout << std::endl;
    std::cout << "N\tStrategyA\tStrategyB\tStrategyC" << std::endl;

    for (int s = 0; s < numSizes; ++s) {
        int N = sizes[s];
        unsigned* baseArr = new unsigned[N];
        for (int i = 0; i < N; ++i) {
            baseArr[i] = i;
        }
        
        unsigned* arrA = new unsigned[N];
        unsigned* arrB = new unsigned[N];
        unsigned* arrC = new unsigned[N];
        
        for (int i = 0; i < N; ++i) {
            arrA[i] = baseArr[i];
            arrB[i] = baseArr[i];
            arrC[i] = baseArr[i];
        }
        
        int* countsC = new int[N]();
        
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
            unsigned key;
            
            if (r % 5 == 0) {
                key = N + r;
            } 
            else {
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
        
        std::default_random_engine rngB(seed);
        begin = std::chrono::steady_clock::now();
        
        for (int r = 0; r < repeats; ++r) {
            unsigned key;
            if (r % 5 == 0) {
                key = N + r;
            } else {
                if (r < repeats * 0.8) {
                    key = hot[distHot(rngB)];
                } else {
                    key = distUniform(rngB);
                }
            }
            searchB(arrB, N, key);
        }
        
        end = std::chrono::steady_clock::now();
        auto timeB = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        
        std::default_random_engine rngC(seed);
        
        for (int i = 0; i < N; ++i) countsC[i] = 0;
        
        begin = std::chrono::steady_clock::now();
        
        for (int r = 0; r < repeats; ++r) {
            unsigned key;
            if (r % 5 == 0) {
                key = N + r;
            } else {
                if (r < repeats * 0.8) {
                    key = hot[distHot(rngC)];
                } else {
                    key = distUniform(rngC);
                }
            }
            searchC(arrC, countsC, N, key);
        }
        
        end = std::chrono::steady_clock::now();
        auto timeC = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        
        std::cout << N << "\t" << timeA << "\t\t" << timeB << "\t\t" << timeC << std::endl;
        
        delete[] baseArr;
        delete[] arrA;
        delete[] arrB;
        delete[] arrC;
        delete[] countsC;
        delete[] hot;
    }
    
    return 0;
}