/////////////////////////////////////////// v2 ///////////////////////////////////////////
#include <iostream>
using namespace std;

void swap(int a, int b);

int main() {
    int a = 10, b = 20;

    cout << "Before swap: a = " << a << ", b = " << b << endl;
    swap(a, b);
    cout << "After swap:  a = " << a << ", b = " << b << endl;
}

void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}



/////////////////////////////////////////// v1 ///////////////////////////////////////////
// #include <iostream>
// using namespace std;

// int main() {
//     int a = 10, b = 20;
//     int* c = &a, * d = &b;

//     cout << "a: " << a << endl << "b: " << b << endl;
//     cout << "*c: " << *c << endl << "*d: " << *d << endl;

//     *c = 30; *d = 40;

//     cout << "a: " << a << endl << "b: " << b << endl;
//     cout << "*c: " << *c << endl << "*d: " << *d << endl;

//     return 0;
// }
