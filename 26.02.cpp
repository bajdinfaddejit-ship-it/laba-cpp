#include <iostream>
using namespace std;

#ifndef N
#define N 3
#endif

#ifndef M
#define M 3
#endif

int* take_N_elements(int* ptr){
    delete[] ptr;
    return nullptr;
}

void swap_arr(int*& ptr0, int*& ptr1){
    int* temp=ptr0;
    ptr0=ptr1;
    ptr1=temp;
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

