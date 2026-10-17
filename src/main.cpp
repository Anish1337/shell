#include <iostream>
#include <string>

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    while (true) {
        std::cout << "$ ";
        std::string input;
        std::getline(std::cin, input);

        // exit condition
        if (input == "exit") {
            break;
        }

        std::cout << input << ": command not found\n";
    }
    return 0;
}
