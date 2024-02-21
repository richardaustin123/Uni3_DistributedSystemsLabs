#include <thread> 
#include <iostream> 
#include <vector> 
#include <string>
#include <mutex>
using namespace std;

vector<string> strings;
mutex mtx;

void addString1() {
    // mtx.lock();
    strings[0] = "Thread 1 was here and pushed 'a'\n";
    strings[1] = "Thread 1 was here and pushed 'b'\n";
    strings[2] = "Thread 1 was here and pushed 'c'\n";
    strings[3] = "Thread 1 was here and pushed 'd'\n";
    strings[4] = "Thread 1 was here and pushed 'e'\n";
    strings[5] = "Thread 1 was here and pushed 'f'\n";
    strings[6] = "Thread 1 was here and pushed 'g'\n";
    strings[7] = "Thread 1 was here and pushed 'h'\n";
    strings[8] = "Thread 1 was here and pushed 'i'\n";
    strings[9] = "Thread 1 was here and pushed 'j'\n";
    // mtx.unlock();
}

void addString2() {
    // mtx.lock();
    strings[10] = "Thread 2 was here and pushed '1'\n";
    strings[11] = "Thread 2 was here and pushed '2'\n";
    strings[12] = "Thread 2 was here and pushed '3'\n";
    strings[13] = "Thread 2 was here and pushed '4'\n";
    strings[14] = "Thread 2 was here and pushed '5'\n";
    strings[15] = "Thread 2 was here and pushed '6'\n";
    strings[16] = "Thread 2 was here and pushed '7'\n";
    strings[17] = "Thread 2 was here and pushed '8'\n";
    strings[18] = "Thread 2 was here and pushed '9'\n";
    strings[19] = "Thread 2 was here and pushed '10'\n";
    // mtx.unlock();
}

int main() {
    strings.resize(20);
    thread t1(addString1);
    thread t2(addString2);

    t1.join();
    t2.join();

    // Print the strings to verify the result
    for (const auto& str : strings) {
        cout << str;
    }

    return 0;
}
