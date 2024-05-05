#include<iostream>
#include<vector>
using namespace std;

void add(vector<vector<int>>* matrix, vector<vector<int>>* newMatrix);

int main () {
    vector<vector<int>> matrix, newMatrix;

    // resize rows
    matrix.resize(3);
    newMatrix.resize(3);

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

    cout << " " << endl;

    add(&matrix, &newMatrix);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << newMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

void add(vector<vector<int>>* matrix, vector<vector<int>>* newMatrix) {

    // Loop through each row 
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            (*newMatrix)[row][col] = 0;
            for (int i = 0; i < 3; i++)
            {
                (*newMatrix)[row][col] += (*matrix)[row][i] + (*matrix)[i][col];
            }
            (*newMatrix)[row][col] -= (*matrix)[row][col];
        }
    }
}