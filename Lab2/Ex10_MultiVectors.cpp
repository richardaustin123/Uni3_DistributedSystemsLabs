// #include <iostream>
// #include <vector>
// #include <thread>
// using namespace std;

// void multiply(vector<int> vect1, vector<int> vect2, vector<int> resultVect);

// int main() {
//     int size = 10;

//     vector<int> vect1, vect2, resultVect;
//     vector<thread> vectThreads;
//     srand((unsigned int)time(0));

//     // spawn thread
//     for (int i = 0; i < size; i++) {
//         vect1.push_back(rand() % 100);
//         vect2.push_back(rand() % 100);
//         resultVect.push_back(0);
//     }

//     // close thread
//     for (int i = 0; i < size; i++) {
//         vectThreads.push_back(thread(multiply, &vect1, &vect2, &resultVect, i));
//     }

//     for (int i = 0; i < size; i++) {
//         vectThreads[i].join();
//     }

//     vector<int> vect1       = {1,2,3};
//     vector<int> vect2       = {4,5,6};
//     vector<int> resultVect  = {0,0,0};

//     // thread t1(multiply, &vect1, &vect2, &resultVect, 0);
//     // thread t2(multiply, &vect1, &vect2, &resultVect, 1);
//     // thread t3(multiply, &vect1, &vect2, &resultVect, 2);

//     // t1.join();
//     // t2.join();
//     // t3.join();

//     for (int i = 0; i < vect1.size(); i++) {
//         cout << vect1[i] << "*" << vect2[i] << " = " << resultVect[i] << "\n";
//     }
// }

// void multiply(vector<int> *vect1, vector<int> *vect2, vector<int> *resultVect, int i) {
//     resultVect->at
// }
// // void multiply(vector<int> *vect1, vector<int> *vect2, vector<int> *resultVect, int i) {
// //     (*resultVect)[i] = (*vect1)[i] * (*vect2)[i];
// // }



// /////////////////////////////////////////// v1 ///////////////////////////////////////////
// #include <iostream>
// #include <vector>
// #include <thread>
// using namespace std;

// vector<int> vect1       = {1,2,3};
// vector<int> vect2       = {4,5,6};
// vector<int> resultVect  = {0,0,0};

// void multiply(int index);

// int main() {
//     thread t1(multiply, 0);
//     thread t2(multiply, 1);
//     thread t3(multiply, 2);

//     t1.join();
//     t2.join();
//     t3.join();

//     for (int i = 0; i < vect1.size(); i++) {
//         multiply(i);
//     }

//     cout << vect1[0] << "*" << vect2[0] << " = " << resultVect[0] << "\n";
//     cout << vect1[1] << "*" << vect2[1] << " = " << resultVect[1] << "\n";
//     cout << vect1[2] << "*" << vect2[2] << " = " << resultVect[2] << "\n";
// }

// void multiply(int i) {
//     resultVect[i] = vect1[i] * vect2[i];
// }


////////////////////////////////// Before thread ///////////////////////////
// #include <iostream>
// #include <vector>

// std::vector<int> v1 = { 2,3,4 };
// std::vector<int> v2 = { 5,6,7 };
// std::vector<int> vResult = { 0,0,0 };

// void multiply(int index)
// {
// 	vResult[index] = v1[index] * v2[index];
// }

// int main()
// {
//     for (int index = 0; index < v1.size(); ++index)
//     {
//         multiply(index);
//     }

//     std::cout << v1[0] << " * " << v2[0] << " = " << vResult[0] << "\n";
//     std::cout << v1[1] << " * " << v2[1] << " = " << vResult[1] << "\n";
//     std::cout << v1[2] << " * " << v2[2] << " = " << vResult[2] << "\n";
// }
