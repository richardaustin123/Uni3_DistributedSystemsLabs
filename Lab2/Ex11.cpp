#include <iostream>
#include <vector>
#include <thread>
using namespace std;

vector<int> vect1 = {1,2,3};
vector<int> vect2 = {4,5,6};
vector<int> vectResult = {0,0,0};

void multiply(int i) {
    vectResult[i] = vect1[i] * vect2[i];
}

int main() {
    thread t1(multiply, 0);
    thread t2(multiply, 1);
    thread t3(multiply, 2);

    t1.join();
    t2.join();
    t3.join();

    cout << vect1[0] << " * " << vect2[0] << " = " << vectResult[0] << "\n";
    cout << vect1[1] << " * " << vect2[1] << " = " << vectResult[1] << "\n";
    cout << vect1[2] << " * " << vect2[2] << " = " << vectResult[2] << "\n"; 
}