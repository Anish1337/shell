#include <iostream>
#include <string>

int main() {

    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (true) {
        std::cout << "$ ";
        std::string input;

        // get line if not EOF
        if (!std::getline(std::cin, input)) {
            break;
        }

        // exit condition
        if (input == "exit") {
            break;
        }

        // echo functionality
        if (input == "echo" || input.substr(0, 5) == "echo ") {
            if (input == "echo") {
                std::cout << "\n";
            } else {
                std::cout << input.substr(5) << "\n";
            }
            continue;
        }

        std::cout << input << ": command not found\n";
    }

    return 0;
}
