
// Aysnc 

#include <iostream>
#include <vector>
#include <thread>
#include <future>

using namespace std;

int addValues(int *num1, int *num2, int *num3);

int main() {
    thread t1;

    int num1, num2, num3;
    int result;
    future<int> res;

    cout << "Enter number 1: ";
    cin >> num1;
    cout << "Enter number 2: ";
    cin >> num2;
    cout << "Enter number 3: ";
    cin >> num3;

    res = async(addValues,&num1, &num2, &num3); // reference with the &
    result = res.get();

    addValues(&num1, &num2, &num3);

    cout << "Answer: " << result << endl;
}

int addValues(int *num1, int *num2, int *num3) { // dereference with the *
    return *num1 + *num2 + *num3;
}