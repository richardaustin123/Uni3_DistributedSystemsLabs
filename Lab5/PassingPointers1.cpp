// Aysnc 

#include <iostream>
#include <vector>
#include <thread>
#include <future>

using namespace std;

double calcAverageValue(vector <int> arrayOfNumbers);

int main() {
    thread t1;

    int amountOfNumbers;
    double result;
    future<double> res;

    cout << "How many numbers do you want to add: ";
    cin >> amountOfNumbers;

    vector <int> arrayOfNumbers;

    for (int i = 0; i < amountOfNumbers; i++) {
        int inputtedNumber;
        cout << "Enter number " << i+1 << ": ";
        cin >> inputtedNumber;
        arrayOfNumbers.push_back(inputtedNumber);
    }

    res = async(calcAverageValue, arrayOfNumbers); 
    result = res.get();

    cout << "Average number: " << result << endl;
}

double calcAverageValue(vector <int> arrayOfNumbers) {
    double averageNumber;
    double sum;

    for (int i = 0; i < arrayOfNumbers.size(); i++) {
        sum += arrayOfNumbers[i];
    }

    averageNumber = sum / arrayOfNumbers.size();
    return averageNumber;
}
