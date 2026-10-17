#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <unordered_set>

// function declaration
std::string find_executable(const std::string& command);

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
                std::string path = find_executable(command);

                if (!path.empty()) {
                    std::cout << command << " is " << path << '\n';
                } else {
                    std::cout << command << ": not found\n";
                }
            }

            continue;
        }

        std::cout << input << ": command not found\n";
    }

    return 0;
}

std::string find_executable(const std::string& command) {
    const char* path_env = std::getenv("PATH");

    if (!path_env) {
        return "";
    }

    std::stringstream ss(path_env);
    std::string directory;

    while (std::getline(ss, directory, ':')) {
        if (directory.empty()) {
            directory = ".";
        }

        std::string full_path = directory + "/" + command;

        struct stat info{};

        if (stat(full_path.c_str(), &info) == 0 && S_ISREG(info.st_mode) &&
            access(full_path.c_str(), X_OK) == 0) {
            return full_path;
        }
    }

    return "";
}
