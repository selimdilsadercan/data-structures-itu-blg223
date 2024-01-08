#include <iostream>
#include <stdio.h> 

using namespace std;


int factorial(int number) {
    // cout << "aktif: " << number << endl; 
    if(number == 0)
        return 1;
    return number * factorial(number-1);
}


int power(int base, int exp) {
    // cout << "işlem: " << base << "^" << exp << endl; 
    if(exp == 0)
        return 1;
    return base * power(base, exp-1);
}


int sayi = 0;
int fibo(int n) {
    // cout << "mevcut: " << n << endl;
    sayi++;
    if(n == 1)
        return 0;
    if(n == 2)
        return 1;
    return fibo(n-1) + fibo(n-2);
}


int arraySum(int* arr, int length, int start) {
    // cout << "arr[" << start << "]" << endl;
    if(start == length - 1)
        return arr[start];
    return arr[start] + arraySum(arr, length, start + 1);
}


int main(){
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};

    // cout << factorial(5) << endl;
    // cout << power(2,4) << endl;
    cout << fibo(17) << endl;
    cout << sayi << endl;
    // cout << arraySum(arr, 10, 0) << endl;

    return 0;
}
