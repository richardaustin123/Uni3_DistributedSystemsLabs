#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;

void sum(vector<vector<int>>* m1, vector<vector<int>>* m2, vector<vector<int>>* mResult, int index);

int main() {
    for (int size = 100; size <= 2000; size += 100)
    {
        int iterations = 10;

        double cumulativeT1 = 0, cumulativeT2 = 0, cumulativeT3 = 0;

        cout << "size: " << size << " ";

        for (int iter = 0; iter < iterations; iter++)
        {
            auto startT1 = chrono::high_resolution_clock::now();

            vector<vector<int>> m1, m2, mResult;
            vector<thread> threadVector;

            m1.resize(size);
            m2.resize(size);
            mResult.resize(size);

            //reset seed for random number generation
            srand((unsigned int)time(0));

            for (int index = 0; index < m1.size(); ++index) {
                m1[index].resize(size);
                m2[index].resize(size);
                mResult[index].resize(size);

                //fill each element of m1 and m2 with a random number between 0 and 100
                for (int j = 0; j < m1[index].size(); ++j) {
                    m1[index][j] = rand() % 100;
                    m2[index][j] = rand() % 100;
                }
            }

            auto startT2 = chrono::high_resolution_clock::now();

            //add corresponding values
            threadVector.push_back(thread(sum, &m1, &m2, &mResult, 0));
            threadVector.push_back(thread(sum, &m1, &m2, &mResult, 1));

            threadVector[0].join();
            threadVector[1].join();

            auto startT3 = chrono::high_resolution_clock::now();

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

            auto end = chrono::high_resolution_clock::now();

            double t1 = chrono::duration_cast<chrono::nanoseconds>(startT2 - startT1).count();
            double t2 = chrono::duration_cast<chrono::nanoseconds>(startT3 - startT2).count();
            double t3 = chrono::duration_cast<chrono::nanoseconds>(end - startT3).count();

            cumulativeT1 += t1;
            cumulativeT2 += t2;
            cumulativeT3 += t3;
        }
        cout << "t1: " << cumulativeT1 / iterations << " t2: " << cumulativeT2 / iterations << " t3: " << cumulativeT3 / iterations << endl;
    }
}

void sum(vector<vector<int>> *m1, vector<vector<int>>* m2, vector<vector<int>>* mResult, int index)
{
    //add corresponding values
    if (index == 0)
    {
        for (int i = 0; i < m1->size()/2; ++i) {
            for (int j = 0; j < m1->at(i).size(); ++j) {
                mResult->at(i)[j] = m1->at(i)[j] + m2->at(i)[j];
            }
        }
    }
    else
    {
        for (int i = m1->size() / 2; i < m1->size(); ++i) {
            for (int j = 0; j < m1->at(i).size(); ++j) {
                mResult->at(i)[j] = m1->at(i)[j] + m2->at(i)[j];
            }
        }
    }
}