#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    string filename = "vector.txt";
    ifstream myfile(filename);
    vector<int> values;
    double sum = 0, averageValue, value;

    if (myfile.is_open()) {
        while (!myfile.eof()) {
            myfile >> value;

            values.push_back(value);
        }

        for (int i = 0; i < values.size(); i++) {
            sum += values[i];
        }

        averageValue = sum / values.size();

        cout << "Average value: " << averageValue << "\n";
    } else {
        cout << "Unable to open file " << filename << "\n";
    }
}
