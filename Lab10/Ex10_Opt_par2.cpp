#include<iostream>
#include<vector>
#include<thread>
#include <chrono>
using namespace std;

void addCols(vector<vector<int>>* matrix, vector<int>* resultCols);
void addRows(vector<vector<int>>* matrix, vector<int>* resultRows);
void addValues(vector<int>* resultCols, vector<int>* resultRows, vector<vector<int>>* newMatrix);
void add(const vector<vector<int>>& matrix, vector<int>& result, bool isRow);
void printVector(const vector<int>& vec);

int main () {
    vector<vector<int>> matrix, newMatrix;
    vector<int> resultCols;
    vector<int> resultRows;

    int matrixSize = 3;

    // resize rows
    matrix.resize(matrixSize);
    newMatrix.resize(matrixSize);
    resultCols.resize(matrixSize);
    resultRows.resize(matrixSize);

    srand((unsigned int)time(0));

    // resize columns
    for (int index = 0; index < matrix.size(); ++index) {
        matrix[index].resize(matrixSize);
        newMatrix[index].resize(matrixSize);

        // fill each element with a random number between 0 and 9
        for (int j = 0; j < matrix[index].size(); ++j) {
            matrix[index][j] = rand() % 10;
        }
    }

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "##########" << endl;

    //////////////////////////////////////////////// Cols and Rows ////////////////////////////////////////////////
    // Add the cols and rows
    // thread threadCols(addCols, &matrix, &resultCols);
    // thread threadRows(addRows, &matrix, &resultRows);
    thread threadCols(add, ref(matrix), ref(resultCols), false);
    thread threadRows(add, ref(matrix), ref(resultRows), true);

    // Wait for the threads to finish
    threadCols.join();
    threadRows.join();

    // Print the cols
    // cout << "result col" << endl;
    // for (int i = 0; i < resultCols.size(); i++) {
    //     cout << resultCols[i] << endl;
    // }

    // // Print the rows
    // cout << "result row" << endl;
    // for (int i = 0; i < resultRows.size(); i++) {
    //     cout << resultRows[i] << " ";
    // }
    // cout << endl;
    printVector(resultCols);
    printVector(resultRows);

    cout << "##########" << endl;
    //////////////////////////////////////////////// New Matrix ////////////////////////////////////////////////
    // Add the values
    thread threadValues(addValues, &resultCols, &resultRows, &newMatrix);

    // Wait for the thread to finish
    threadValues.join();

    // Print the new matrix
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            cout << newMatrix[i][j] - matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

void add(const vector<vector<int>>& matrix, vector<int>& result, bool isRow) {
    int size = matrix.size();
    for (int i = 0; i < size; i++) {
        int sum = 0;
        for (int j = 0; j < size; j++) {
            sum += isRow ? matrix[i][j] : matrix[j][i];
        }
        result[i] = sum;
    }
}

void printVector(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

void addValues(vector<int>* resultCols, vector<int>* resultRows, vector<vector<int>>* newMatrix) {
    int matrixSize = resultCols->size();
    for (int row = 0; row < matrixSize; row++) {
        for (int col = 0; col < matrixSize; col++) {
            (*newMatrix)[row][col] = (*resultCols)[col] + (*resultRows)[row];
        }
    }
}

// void add(vector<vector<int>>* matrix, vector<vector<int>>* newMatrix) {

//     // Loop through each row 
//     for (int row = 0; row < matrixSize; row++)
//     {
//         for (int col = 0; col < matrixSize; col++)
//         {
//             (*newMatrix)[row][col] = 0;
//             for (int i = 0; i < matrixSize; i++)
//             {
//                 (*newMatrix)[row][col] += (*matrix)[row][i] + (*matrix)[i][col];
//             }
//             (*newMatrix)[row][col] -= (*matrix)[row][col];
//         }
//     }
// }