#include <vector>
#include <cstdint>
#include <array>

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

    static constexpr std::array<uint8_t, 256> buildTable(); 
};