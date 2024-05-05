#include<iostream>
#include<vector>
#include<thread>
#include <chrono>
using namespace std;

void addCols(vector<vector<int>>* matrix, vector<int>* resultCols);
void addRows(vector<vector<int>>* matrix, vector<int>* resultRows);
void addValues(vector<int>* resultCols, vector<int>* resultRows, vector<vector<int>>* newMatrix);

int main () {
    vector<vector<int>> matrix, newMatrix;
    vector<int> resultCols;
    vector<int> resultRows;

    // resize rows
    matrix.resize(3);
    newMatrix.resize(3);
    resultCols.resize(3);
    resultRows.resize(3);

    srand((unsigned int)time(0));

    // resize columns
    for (int index = 0; index < matrix.size(); ++index) {
        matrix[index].resize(3);
        newMatrix[index].resize(3);

        // fill each element with a random number between 0 and 9
        for (int j = 0; j < matrix[index].size(); ++j) {
            matrix[index][j] = rand() % 10;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "##########" << endl;

    //////////////////////////////////////////////// Cols and Rows ////////////////////////////////////////////////
    // Add the cols and rows
    thread threadCols(addCols, &matrix, &resultCols);
    thread threadRows(addRows, &matrix, &resultRows);

    // Wait for the threads to finish
    threadCols.join();
    threadRows.join();

    // Print the cols
    cout << "result col" << endl;
    for (int i = 0; i < resultCols.size(); i++) {
        cout << resultCols[i] << endl;
    }

    // Print the rows
    cout << "result row" << endl;
    for (int i = 0; i < resultRows.size(); i++) {
        cout << resultRows[i] << " ";
    }
    cout << endl;

    cout << "##########" << endl;
    //////////////////////////////////////////////// New Matrix ////////////////////////////////////////////////
    // Add the values
    thread threadValues(addValues, &resultCols, &resultRows, &newMatrix);

    // Wait for the thread to finish
    threadValues.join();

    // Print the new matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << newMatrix[i][j] - matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

void addCols(vector<vector<int>>* matrix, vector<int>* resultCols) {
    // Loop through each column
    for (int col = 0; col < 3; col++) {
        int sum = 0;
        // Loop through each row
        for (int row = 0; row < 3; row++) {
            // Add the current element to the sum
            sum += (*matrix)[row][col];
        }

        // Store the sum in resultCols
        (*resultCols)[col] = sum;
    }
}


void addRows(vector<vector<int>>* matrix, vector<int>* resultRows) {
    // Loop through each row
    for (int row = 0; row < 3; row++) {
        int sum = 0;
        // Loop through each col
        for (int col = 0; col < 3; col++) {
            // Add the current element to the sum
            sum += (*matrix)[row][col];
        }

        // Store the sum in resultCols
        (*resultRows)[row] = sum;
    }
}

void addValues(vector<int>* resultCols, vector<int>* resultRows, vector<vector<int>>* newMatrix) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            (*newMatrix)[row][col] = (*resultCols)[col] + (*resultRows)[row];
        }
    }
}

