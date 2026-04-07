#include <iostream>

using namespace std;

bool is_powerof2(int t) {
    int ans=0;
    while (true){
    if (t%2==0){
        if (t==1){
            ans=1;
            break;
        }
        t=t/2;
    }
    if (t%2!=0){
        ans=0;
        break;
    }
}
    return 0;
}

int main() {
int n=10;
cout << is_powerof2(n) << endl;
return 0;
}