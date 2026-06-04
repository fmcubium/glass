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

    
};