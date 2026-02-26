#include <iostream>
#include <cmath>

int prefics_increment(int&);
int postfics_increment(int&);
float prefics_increment(float&);
float power_sqr(float);
int power_sqr(int);

using namespace std;


int main() {
    double x = 12.5;
    cout << x << endl;
    cout << power_sqr(static_cast<float>(x)) << endl;
    return 0;
}
   


int prefics_increment(int& value){
    value +=1;
    return value;
}

float prefics_increment(float& value){
    value +=1;
    return value;
}

int postfics_increment(int& value){
    int copy = value;
    value +=1;
    return copy;
}

int power_sqr(int value){
    return value * value;
}

float power_sqr(float value){
    return value * value;
}
