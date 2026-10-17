#include <iostream>
#include <string>
#include <unordered_set>
int main() {

    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    // valid types
    const std::unordered_set<std::string> builtins = {"echo", "exit", "type"};

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
        if (input == "echo" || input.starts_with("echo ")) {
            if (input == "echo") {
                std::cout << "\n";
            } else {
                std::cout << input.substr(5) << "\n";
            }
            continue;
        }

        // types
        if (input.starts_with("type ")) {
            std::string command = input.substr(5);

            if (builtins.contains(command)) {
                std::cout << command << " is a shell builtin\n";
            } else {
                std::cout << command << ": not found\n";
            }

            continue;
        }

        std::cout << input << ": command not found\n";
    }

    return 0;
}
