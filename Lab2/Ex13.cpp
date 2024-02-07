#include <iostream> 
#include <vector> 
#include <fstream> 
#include <iomanip>
using namespace std;

int main() {
    vector<vector<int> > m1, m2, mResult;

    m1.resize(10); m2.resize(10); mResult.resize(10);

    //reset seed for random number generation
    srand((unsigned int) time(0));

    for (int index = 0; index < m1.size(); ++index) {
        m1[index].resize(10); m2[index].resize(10); mResult[index].resize(10);

        //fill each element of m1 and m2 with a random number between 0 and 100
        for (int j = 0; j < m1[index].size(); ++j) {
            m1[index][j] = rand() % 100; m2[index][j] = rand() % 100;
        }
    }

    //add corresponding values
    for (int i = 0; i < m1.size(); ++i) {
        for (int j = 0; j < m1[i].size(); ++j) {
            mResult[i][j] = m1[i][j] + m2[i][j];
        }
    }

    //write the result to a file
    ofstream outputFile("result.txt");

    if (outputFile.is_open()) {
        for (int i = 0; i < m1.size(); ++i) {
            for (int j = 0; j < m1[i].size(); ++j) {
                outputFile << setw(3) << m1[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile << endl << endl;

        for (int i = 0; i < m2.size(); ++i) {
            for (int j = 0; j < m2[i].size(); ++j) {
                outputFile << setw(3) << m2[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile << endl << endl;

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
