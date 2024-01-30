#include <iostream>
#include <vector>
using namespace std;

int main()
{
    std::vector<int> values;
    double sum = 0, averageValue;
    int value;

    for (int i = 0; i < 5; i++)
    {
        cout << "Insert value " << i << ": ";
        cin >> value;

        values.push_back(value);
    }

    for (int i = 0; i < values.size(); i++)
    {
        sum += values[i];
    }

    averageValue = sum / values.size();

    cout << "Average value: " << averageValue << "\n";
}


/////////////////////////////////////////// My implementation ///////////////////////////////////////////
// #include <iostream>
// using namespace std;

// void averageNumber() {
//     // array of number
//     int numbers[5];
//     cout << "Enter 5 numbers: \n";
//     for (int i = 0; i < 5; i++) {
//         cout << "\nNumber " << i+1 << ": ";
//         cin >> numbers[i];
//     }
//     int averageNumberInt;
//     for (int i = 0; i < 5; i++) {
//         averageNumberInt += numbers[i];
//         if (i == 4) {
//             averageNumberInt = averageNumberInt / 5;
//         }
//     }

//     cout << "\nThe average number is " << averageNumberInt;
// }

// int main() {
//     averageNumber();
// }