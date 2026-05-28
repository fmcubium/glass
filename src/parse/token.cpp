#include "parse/token.h"

// Getters

Token::Type Token::getType() {
    return type;
}

std::string Token::getLiteral() {
    return literal;
}