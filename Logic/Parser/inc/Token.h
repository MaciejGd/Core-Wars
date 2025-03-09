#pragma once

#include <array>
#include <string>

enum TokenType {
    SEPARATOR,
    LABEL,
    INSTRUCTION,
    ADDRESS_MODE
};

// token can be either:
// label of a line 
// separator (, , ; )
// arithmetic operator ( + , - , )
// address mode (#, $, <, >, {, })
// modifiers ()
// every letter will be down cased
constexpr std::array<std::string, 7> tkn_modifiers = {".a", ".b", ".ab", ".ba", ".f", ".x", ".i"};
constexpr std::array<std::string, 19> tkn_operations = {"DAT", "MOV", "ADD", "SUB", "MUL", "DIV", "MOD", 
                    "JMP", "JMZ", "JMN", "DJN", "SPL", "CMP", "SEQ", "SNE", "SLT", "LDP", "STP", "NOP"};
constexpr std::array<char, 2> tkn_separators = {',', ';'};
constexpr std::array<char, 6> tkn_address_modes = {'#', '$', '<', '>', '{', '}'};

class Token {
private:
    TokenType m_type;
    std::string m_val;
public:
    Token() {};
    Token(TokenType type, const std::string& value): m_type(type), m_val(value) {};
    const TokenType type() const { return m_type; };
    const std::string value() const { return m_val; };
};

