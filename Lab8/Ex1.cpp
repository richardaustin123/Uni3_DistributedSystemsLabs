#include "ThreadPool.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <thread>

using namespace std;

int sum(int i, vector<vector<int>>* m1, vector<vector<int>>* m2, vector<vector<int>>* mResult);

int main()
{
    ThreadPool pool(thread::hardware_concurrency());
    vector<vector<int>> m1, m2, mResult;
    vector<future<int>> results;

    m1.resize(10);
    m2.resize(10);
    mResult.resize(10);

    //reset seed for random number generation
    srand((unsigned int)time(0));

    for (int index = 0; index < m1.size(); ++index)
    {
        m1[index].resize(10);
        m2[index].resize(10);
        mResult[index].resize(10);

        //fill each element of m1 and m2 with a random number between 0 and 100
        for (int j = 0; j < m1[index].size(); ++j)
        {
            m1[index][j] = rand() % 100;
            m2[index][j] = rand() % 100;
        }
    }

    for (int i = 0; i < m1.size(); ++i)
    {
        results.push_back(pool.enqueue(sum, i, &m1, &m2, &mResult));
    }

    for (int i = 0; i < results.size(); ++i)
    {
		results[i].get();
	}

    //write the result to a file
    ofstream outputFile("result.txt");
    if (outputFile.is_open())
    {
        for (int i = 0; i < m1.size(); ++i)
        {
            for (int j = 0; j < m1[i].size(); ++j)
            {
                outputFile << setw(3) << m1[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile << endl;
        outputFile << endl;

        for (int i = 0; i < m2.size(); ++i)
        {
            for (int j = 0; j < m2[i].size(); ++j)
            {
                outputFile << setw(3) << m2[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile << endl;
        outputFile << endl;

        for (int i = 0; i < mResult.size(); ++i)
        {
            for (int j = 0; j < mResult[i].size(); ++j)
            {
                outputFile << setw(3) << mResult[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile.close();
    }
    else
    {
        cerr << "Unable to open file" << endl;
    }
}

int sum(int i, vector<vector<int>>* m1, vector<vector<int>>* m2, vector<vector<int>>* mResult)
{
    for (int j = 0; j < m1->at(i).size(); ++j)
    {
		mResult->at(i)[j] = m1->at(i)[j] + m2->at(i)[j];
	}

    return 0;
}