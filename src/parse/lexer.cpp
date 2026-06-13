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

void Lexer::lexIdentifier() {
    if(input.empty() || (!Lexer::isTrait(input[0], Lexer::Alpha) && input[0] != '_'))
        throw std::logic_error("Failure to meet function precondition");

    std::size_t len = 1;
    while(len < input.size() && (Lexer::isTrait(input[len], Lexer::Alpha | Lexer::Digit) || input[len] == '_'))
        len++;
    
    Token t(Token::Identifier, input.substr(0, len));
    tokens.push_back(t);
    input = input.substr(len);
}

void Lexer::lexNumber() { // i have no clue if this works
    if(input.length() < 2 || 
        !((Lexer::isTrait(input[1], Lexer::Digit) && (input[0] == '+' || input[0] == '-')) || 
            Lexer::isTrait(input[0], Lexer::Digit)))
        throw std::logic_error("Failure to meet function precondition");

    std::size_t len = 1;
    while(len < input.size() && Lexer::isTrait(input[len], Lexer::Digit))
        len++;

    if(len < input.size() - 1 && (input[len] == '.' || input[len] == 'e')) {
        // float logic
        bool dec = (input[len] == '.');
        len++;
        while(len < input.size() && Lexer::isTrait(input[len], Lexer::Digit))
            len++;

        if(dec && len < input.size() - 1 && input[len] == 'e') {
            if(input[len + 1] == '+' || input[len + 1] == '-')
                len += 2;
            else
                len++;
            
            while(len < input.size() && Lexer::isTrait(input[len], Lexer::Digit))
                len++;

        }

        Token t(Token::FloatLiteral, input.substr(0, len));
        tokens.push_back(t);
        input = input.substr(len);

    }
    else {
        Token t(Token::IntLiteral, input.substr(0, len));
        tokens.push_back(t);
        input = input.substr(len);

    }
    
}

void Lexer::lexOperator() {
    if(input.empty() || !(input[0] == '.' || Lexer::isTrait(input[0], Lexer::Operator)))
        throw std::logic_error("Failure to meet function precondition");

    std::size_t len = 1;
    if(input[0] == '.') {
        Token t(Token::Operator, input.substr(0, len));
        tokens.push_back(t);
        input = input.substr(len);

        return;
    }
    if(len < input.size() && input.substr(0, len + 1) == "++") {
        len++;

        Token t(Token::Operator, input.substr(0, len));
        tokens.push_back(t);
        input = input.substr(len);

        return;
    }
    if(len < input.size() && input[0] == '-' && (input[len] == '-' || input[len] == '>')) {
        len++;

        Token t(Token::Operator, input.substr(0, len));
        tokens.push_back(t);
        input = input.substr(len);

        return;
    }

    if(len < input.size() && input[len] == '=')
        len++;

    
    Token t(Token::Operator, input.substr(0, len));
    tokens.push_back(t);
    input = input.substr(len);
    
}