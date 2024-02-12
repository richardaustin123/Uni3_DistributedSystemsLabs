#include <iostream>
#include <vector>
#include <thread>
using namespace std;

void multiply(vector<int> a, vector<int> b, vector<int>* result, int index) {
    result->at(index) = a[index] * b[index];
}

int main() {
    vector<int> vect1 = {1,2,3,4};
    vector<int> vect2 = {5,6,7,8};
    vector<int> vectResult = {0,0,0,0};
    vector<thread> vectThreads;
    
    thread t1(multiply, vect1, vect2, &vectResult, 0);
    thread t2(multiply, vect1, vect2, &vectResult, 1);
    thread t3(multiply, vect1, vect2, &vectResult, 2);
    thread t4(multiply, vect1, vect2, &vectResult, 3);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout << vect1[0] << " * " << vect2[0] << " = " << vectResult[0] << "\n";
    cout << vect1[1] << " * " << vect2[1] << " = " << vectResult[1] << "\n";
    cout << vect1[2] << " * " << vect2[2] << " = " << vectResult[2] << "\n"; 
    cout << vect1[3] << " * " << vect2[3] << " = " << vectResult[3] << "\n"; 
}