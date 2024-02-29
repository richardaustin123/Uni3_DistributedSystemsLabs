#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <future>

using namespace std;

void sum(std::vector<std::vector<int>>* m1, std::vector<std::vector<int>>* m2, std::promise<std::vector<std::vector<int>>> &&result, int index);

int main() {
    int size = 10;

    std::cout << "size: " << size << " " << endl;

    std::vector<std::vector<int>> m1, m2, mResult, part1, part2;

    std::promise<std::vector<std::vector<int>>> prom1, prom2;
    std::future<std::vector<std::vector<int>>> fut1 = prom1.get_future();
    std::future<std::vector<std::vector<int>>> fut2 = prom2.get_future();

    m1.resize(size);
    m2.resize(size);

    //reset seed for random number generation
    srand((unsigned int)time(0));

    for (int index = 0; index < m1.size(); ++index) {
        m1[index].resize(size);
        m2[index].resize(size);

        //fill each element of m1 and m2 with a random number between 0 and 100
        for (int j = 0; j < m1[index].size(); ++j) {
            m1[index][j] = rand() % 100;
            m2[index][j] = rand() % 100;
        }
    }

    //add corresponding values
    std::thread t1(sum, &m1, &m2, std::move(prom1), 0);
    std::thread t2(sum, &m1, &m2, std::move(prom2), 1);

    t1.join();
    t2.join();

    part1 = fut1.get();
    part2 = fut2.get();

    for (int i = 0; i < part1.size(); i++)
    {
        mResult.push_back(part1[i]);
    }

    for (int i = 0; i < part2.size(); i++)
    {
        mResult.push_back(part2[i]);
    }

    //write the result to a file
    std::ofstream outputFile("result.txt");

    if (outputFile.is_open()) {
        for (int i = 0; i < m1.size(); ++i) {
            for (int j = 0; j < m1[i].size(); ++j) {
                outputFile << std::setw(3) << m1[i][j] << " ";
            }
            outputFile << std::endl;
        }
        outputFile << std::endl << std::endl;

        for (int i = 0; i < m2.size(); ++i) {
            for (int j = 0; j < m2[i].size(); ++j) {
                outputFile << std::setw(3) << m2[i][j] << " ";
            }
            outputFile << std::endl;
        }
        outputFile << std::endl << std::endl;

        for (int i = 0; i < mResult.size(); ++i) {
            for (int j = 0; j < mResult[i].size(); ++j) {
                outputFile << std::setw(3) << mResult[i][j] << " ";
            }
            outputFile << std::endl;
        }
        outputFile.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }
}

void sum(std::vector<std::vector<int>>* m1, std::vector<std::vector<int>>* m2, std::promise<std::vector<std::vector<int>>> &&result, int index)
{
    std::vector<std::vector<int>> res;

    //add corresponding values
    if (index == 0)
    {
        res.resize(m1->size() / 2);

        for (int i = 0; i < m1->size() / 2; ++i) {
            for (int j = 0; j < m1->at(i).size(); ++j) {
                res[i].push_back(m1->at(i)[j] + m2->at(i)[j]);
            }
        }
    }
    else
    {
        int r = 0;
        res.resize(m1->size() / 2);

        for (int i = m1->size() / 2; i < m1->size(); ++i) {
            for (int j = 0; j < m1->at(i).size(); ++j) {
                res[r].push_back(m1->at(i)[j] + m2->at(i)[j]);
            }
            r++;
        }
    }

    result.set_value(res);
}