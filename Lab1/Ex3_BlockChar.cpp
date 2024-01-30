#include <iostream>
using namespace std;

void blockOfChar(char ch, int rows, int cols) {
    for(int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            cout << ch;
	    }
        cout << "\n";
    }
}

int main() {
    blockOfChar('*', 5, 4);
}
