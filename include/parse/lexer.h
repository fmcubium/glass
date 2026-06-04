#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <array>
#include <stdexcept>

#include "parse/token.h"

class Lexer {
    enum Traits : std::uint8_t {
        None = 0,
        Alpha = 1, //QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm
        Digit = 1 << 1, // 1234567890
        Space = 1 << 2, // <SPACE> \n \r \t 
        Operator = 1 << 3, // =+-/*<>!&|~%^
        Separator = 1 << 4, // ,:;
        Bracket = 1 << 5 // ()[]{}
    };

    
    // character table used to check for different character types
    static constexpr std::array<std::uint8_t, 256> buildTable() {
        std::array<std::uint8_t, 256> t{};
        for(int i = 0; i < 256; i++) {
            char c = static_cast<char>(i);

            if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
                t[i] |= Alpha;
            if (c >= '0' && c <= '9') 
                t[i] |= Digit;
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r' ) 
                t[i] |= Space;
            if (c == '=' || c == '+' || c == '-' || c == '/' || c == '*' || c == '<' || 
                c == '>' || c == '!' || c == '&' || c == '|' || c == '~' || c == '%' || c == '^')
                t[i] |= Operator;
            if (c == ',' || c == ':' || c == ';')
                t[i] |= Separator;
            if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}')
                t[i] |= Bracket;
        }

        return t;
    } 
    static const std::array<std::uint8_t, 256> table;
    
    // checks if `check` falls in the category specified by `mask`
    static inline bool isTrait(char check, std::uint8_t mask) {
        return (table[static_cast<unsigned char>(check)] & mask) != 0;
    }

    // checks if `check` matches `desired`. Really just a wrapper I might get rid of
    static inline bool is(char check, char desired) {
        return check == desired;
    }

    // input str
    std::string input;

    // tokens
    std::vector<Token> tokens;

    // lexes and ejects whitespace
    void lexWhitespace();

    // lexes and ejects comments
    void lexComment();

    // lexes and stores identifiers
    void lexIdentifier();

    // lexes and stores integers and/or decimals
    void lexNumber();

    // lexes and stores operators
    void lexOperator();

    // lexes and stores character literals
    void lexCharacter();

    // lexes and stores string literals
    void lexString();

    // lexes and stores any other legal characters
    void lexOther();

public:

    // constructors for setup
    Lexer(std::string& input) : input(input) {}
    Lexer(std::string input = "") : input(input) {}

    // lexes the module and returns the resulting tokens
    std::vector<Token> lex();
};

inline constexpr std::array<std::uint8_t, 256> Lexer::table = Lexer::buildTable();