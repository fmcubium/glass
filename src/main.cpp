#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>

#define DEBUG //to be moved to a debug header later

int main(int argc, char** argv) {
    // #ifdef DEBUG
    //     static_assert(false, "ERROR: DEBUG must not be defined on non-test builds.");
    // #endif

    #ifdef DEBUG
        std::cout << argc << std::endl;
    #endif

    std::vector<std::string> filenames;
    std::string suffix = ".gls";
    for(int i = 1; i < argc; i++) {
        std::string temp = argv[i];
        if(!(temp.size() >= suffix.size() && temp.compare(temp.size() - suffix.size(), suffix.size(), suffix) == 0))
            throw std::runtime_error("Inputted file is not a Glass source file.");

        // TODO: This will handle directories in the future, but not right now.
        filenames.push_back(temp);
    }
}