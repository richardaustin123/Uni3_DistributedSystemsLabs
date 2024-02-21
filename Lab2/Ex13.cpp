#include <iostream> 
#include <vector> 
#include <fstream> 
#include <iomanip>
using namespace std;

int main() {
    vector<vector<int> > m1, m2, mResult;

    // Change number of rows of each row
    m1.resize(10); 
    m2.resize(10); 
    mResult.resize(10);

    // reset seed for random number generation
    srand((unsigned int) time(0));

    // Generate teh 3 matrixes 
    for (int i = 0; i < m1.size(); ++i) {
        // Change number of column of each row
        m1[i].resize(10); 
        m2[i].resize(10); 
        mResult[i].resize(10);

        // fill each element of m1 and m2 with a random number between 0 and 100
        for (int j = 0; j < m1[i].size(); ++j) {
            m1[i][j] = rand() % 100; 
            m2[i][j] = rand() % 100;
        }
    }

    // add corresponding values from m1 and m2
    for (int i = 0; i < m1.size(); ++i) {
        for (int j = 0; j < m1[i].size(); ++j) {
            mResult[i][j] = m1[i][j] + m2[i][j];
        }
    }

    // write the result to a file
    ofstream outputFile("result.txt");

    if (outputFile.is_open()) {
        // File opened 
        // Print matrix 1
        for (int i = 0; i < m1.size(); ++i) {
            for (int j = 0; j < m1[i].size(); ++j) {
                outputFile << setw(3) << m1[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile << endl << endl;

        // Print matrix 2
        for (int i = 0; i < m2.size(); ++i) {
            for (int j = 0; j < m2[i].size(); ++j) {
                outputFile << setw(3) << m2[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile << endl << endl;

        // Print result matrix 
        for (int i = 0; i < mResult.size(); ++i) {
            for (int j = 0; j < mResult[i].size(); ++j) {
                outputFile << setw(3) << mResult[i][j] << " ";
            }
	        outputFile << endl;
        }
        outputFile.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}
