#pragma once

#include <stdexcept>
#include <string>

#include "parse/token.h"

namespace GlassError {
    // errors during the source code loading phase
    class LoadError : public std::runtime_error {
    public:
        LoadError(const std::string& description) : std::runtime_error(description) {}
        LoadError(const char* description) : std::runtime_error(description) {}
        LoadError(const LoadError& other) : std::runtime_error(other) {}
    };

    // errors during lexing
    class LexerError : public std::runtime_error {
    public:
        LexerError(const std::string& description, const char next) : std::runtime_error(description) {}
        LexerError(const char* description, const char next) : std::runtime_error(description) {}
        LexerError(const LexerError& other) : std::runtime_error(other) {}

        const char* what() const noexcept;
    };
};