#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <fstream>
#include <sstream>

#include "glass_error.h"
#include "parse/ast.h"
#include "parse/lexer.h"

#define DEBUG //to be moved to a debug header later

void parse(std::vector<Ast::Module>& modules, std::string filename, std::size_t index) {
    std::ifstream file(filename);
    if(!file.is_open())
        throw GlassError::LoadError("Inputted glass source file not found.");

    std::ostringstream srcStream;
    srcStream << file.rdbuf();

    // Lexer lexer(srcStream.str());
    // std::vector<Token> tokens = lexer.lex();
}

int main(int argc, char** argv) {
    // #ifdef DEBUG
    //     static_assert(false, "ERROR: DEBUG must not be defined on non-test builds.");
    // #endif

    #ifdef DEBUG
        std::cout << argc << std::endl;
    #endif

    std::vector<std::string> filenames;
    std::string suffix = ".gls";
    
    try {
        for(int i = 1; i < argc; i++) {
            std::string temp = argv[i];
            if(!(temp.size() >= suffix.size() && temp.compare(temp.size() - suffix.size(), suffix.size(), suffix) == 0))
                throw GlassError::LoadError("Inputted file is not a Glass source file.");

            // TODO: This will handle directories in the future, but not right now.
            filenames.push_back(temp);
        }


    } catch(GlassError::LoadError& e) {
        std::cout << "Loading Error: " << e.what() << std::endl;
    }
}