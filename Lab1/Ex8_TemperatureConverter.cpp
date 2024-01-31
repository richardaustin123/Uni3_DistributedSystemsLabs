#include <iostream>
using namespace std;

void tempConverter() {
    double tempIn, tempOut;
    char celOrFar;

    cout << "Please enter C or F ";
    cin >> celOrFar;
    cout << "\nPlease enter your temperature ";
    cin >> tempIn;

    if (celOrFar == 'C') {
        tempOut = (tempIn * (9/5)) + 32;
    } else if (celOrFar == 'F') {
        tempOut = (tempIn - 32) * (9/5);
    } else {
        cout << "Invalid\n";
    }

    cout << "\n" << tempOut;
}


int main () {
    tempConverter();
}