/////////////////////////////////////////// Exercise 1 ///////////////////////////////////////////
// #include <iostream>
// using namespace std;

// int main() {
//     int a = 10, b = 20;
//     int* c = &a, * d = &b;

//     cout << "a: " << a << std::endl << "b: " << b << std::endl;
//     cout << "*c: " << *c << std::endl << "*d: " << *d << std::endl;

//     *c = 30; *d = 40;

//     cout << "a: " << a << std::endl << "b: " << b << std::endl;
//     cout << "*c: " << *c << std::endl << "*d: " << *d << std::endl;

//     return 0;
// }

/////////////////////////////////////////// Exercise 2 ///////////////////////////////////////////
#include <iostream>
using namespace std;

void swap(int a, int b);

int main() {
    int a = 10, b = 20;

    cout << "Before swap: a = " << a << ", b = " << b << endl;
    swap(a, b);
    cout << "After swap: a = " << a << ", b = " << b << endl;
}

void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}
