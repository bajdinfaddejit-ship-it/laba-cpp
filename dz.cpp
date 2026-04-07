#include <iostream>
using namespace std;

#ifndef N
#define N 3
#endif

#ifndef M
#define M 3
#endif

void sort2d(int (&array)[N][M]){
    int arrlin[N*M];
    for (unsigned i = 0; i < N ; ++i) {
        for (unsigned j = 0; j < M ; ++j){
            arrlin[j+i*M]=array[i][j];
        }
    }
    unsigned total = N * M;
    for (unsigned gap = total / 2; gap > 0; gap /= 2) {
    for (unsigned i = gap; i < total; i++) {
        int temp = arrlin[i];
        unsigned j;
        for (j = i; j >= gap && arrlin[j - gap] > temp; j -= gap) {
            arrlin[j] = arrlin[j - gap];
        }
        arrlin[j] = temp;
        }
    }
    for (unsigned i = 0; i < N ; ++i) {
        for (unsigned j = 0; j < M ; ++j){
            array[i][j]=arrlin[j+i*M];
        }
    }
}


int main() {
int array[3][3]={1,2,3,1,2,3,1,2,3};
int arrlin[3*3],arrans[3][3];
    for (unsigned i = 0; i < 3 ; ++i) {
        for (unsigned j = 0; j < 3 ; ++j){
            arrlin[j+i*3]=array[i][j];
        }
    }
    cout<<array<<arrlin<<endl;
    return 0;
}

