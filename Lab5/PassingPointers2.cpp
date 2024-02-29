// Aysnc 

#include <iostream>
#include <vector>
#include <thread>
#include <future>

using namespace std;

vector<int> addVectors(vector<int> vector1, vector<int> vector2);

ostream& operator << (ostream& o, std::vector<int> array) {
    for (int element: array)
        o << element << " ";
    return o;
}

int main() {
    thread t1;

    vector <int> vector1 = {1,2,3};
    vector <int> vector2 = {4,5,6};
    vector <int> result;
    future<vector<int>> res;

    res = async(addVectors, vector1, vector2); 
    result = res.get();

    cout << "Joined vectors: " << result << endl;
}

vector<int> addVectors(vector<int> vector1, vector<int> vector2) {
    vector<int> resultVector;
    
    // loop vector1
    for (int i = 0; i < vector1.size(); i++) {
        resultVector.push_back(vector1[i]);
    }

    // loop vector2
    for (int i = 0; i < vector2.size(); i++) {
        resultVector.push_back(vector2[i]);
    }

    return resultVector;
}
