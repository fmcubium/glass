#include "parse/lexer.h"

using std::uint8_t, std::vector;

// Private helper functions
void Lexer::lexWhitespace() {
    if(input.empty() || !Lexer::isTrait(input[0], Lexer::Space))
        throw std::logic_error("Failure to meet function precondition");

    std::size_t len = 1;
    while(len < input.size() && Lexer::isTrait(input[len], Lexer::Space))
        len++;

    input = input.substr(len);
}

void Lexer::lexComment() {
    if(input.length() < 2 || !(input[0] == '/' && input[1] == '/'))
        throw std::logic_error("Failure to meet function precondition");

    std::size_t len = 2;
    while(len < input.size() && input[len] != '\n' && input[len] != '\r')
        len++;
    
    input = input.substr(len);
}