#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vect1 = {1,2,3};
    vector<int> vect2 = {4,5,6};
    vector<int> resultVect = {0,0,0};

    for (int i = 0; i < vect1.size(); i++) {
        resultVect[i] = vect1[i] * vect2[i];
    }

    cout << vect1[0] << "*" << vect2[0] << " = " << resultVect[0] << "\n";
    cout << vect1[1] << "*" << vect2[1] << " = " << resultVect[1] << "\n";
    cout << vect1[2] << "*" << vect2[2] << " = " << resultVect[2] << "\n";
}