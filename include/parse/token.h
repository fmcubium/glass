#pragma once

#include <string>

class Token {
public:
    // Types of tokens to be classified
    enum Type {
        Identifier,
        IntLiteral,
        DecLiteral,
        Operator,
        CharLiteral,
        StringLiteral,
        Miscellaneous
    };

private:
    Type type;
    std::string literal;
    
public:
    // Constructor
    Token(Type type, std::string literal) : type(type), literal(literal) {}

    // getters
    Type getType();
    std::string getLiteral();

};