/////////////////////////////////////////// v4 ///////////////////////////////////////////
#include <iostream>
#include <string>

int main() {
    std::string name;
    int age;

    std::cout << "What's your name? ";

    std::cin >> name;

    std::cout << "Hello " << name << "!\n";

    std::cout << "How old are you? ";

    std::cin >> age;

    std::cout << "You are " << age << " years old\n";
}

/////////////////////////////////////////// v3 ///////////////////////////////////////////
// #include <iostream>
// #include <string>

// int main() {
//     std::string name;

//     std::cin >> name;

//     std::cout << "Hello " << name << "!\n";
// }

/////////////////////////////////////////// v2 ///////////////////////////////////////////
// #include <iostream>
// #include <string>

// int main() {
//     std::string name = "Richard";

//     std::cout << "Hello " << name << "!\n";
// }

/////////////////////////////////////////// v1 ///////////////////////////////////////////
// #include <iostream>
// #include <string>

// int main() {
//     std::string name = "Richard";

//     std::cout << "Hello ";
//     std::cout << name;
//     std::cout << "!\n";
// }