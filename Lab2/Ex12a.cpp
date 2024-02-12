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

    for (int i = 0; i < vectResult.size(); i++) {
        vectThreads.push_back(thread(multiply, vect1, vect2, &vectResult, i));
    }

    for (int i = 0; i < vectResult.size(); i++) {
        vectThreads[i].join();
    }

    for (int i = 0; i < vectResult.size(); i++) {
        cout << vect1[i] << " * " << vect2[i] << " = " << vectResult[i] << "\n";
    }
}