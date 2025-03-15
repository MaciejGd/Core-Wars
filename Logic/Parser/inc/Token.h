#pragma once

#include <array>
#include <set>
#include <string>
#include <string_view>

enum TokenType {
    OPERATIONS,
    SEPARATOR,
    LABEL,
    MODIFIERS,
    ADDRESS_MODE,
    ARITHM_OPS,
    NUMERICAL_VAL
};


constexpr std::array<std::string, 7> tkn_modifiers = {".a", ".b", ".ab", ".ba", ".f", ".x", ".i"};
constexpr std::array<std::string, 19> tkn_operations = {"dat", "mov", "add", "sub", "mul", "div", "mod", 
                    "jmp", "jmz", "jmn", "djn", "spl", "cmp", "seq", "sne", "slt", "ldp", "stp", "nop"};
constexpr std::array<char, 5> tkn_ar_ops = {'+', '-', '/', '*', '%'}; // five arithmetic operations
//constexpr std::array<char, 2> tkn_separators = {',', ';'}; // this is actually not needed as ; will handle 
constexpr char tkn_comment = ';'; // wont be parsed
constexpr char tkn_coma = ',';
constexpr std::array<char, 6> tkn_address_modes = {'#', '$', '<', '>', '{', '}'};


class Token {
private:
    int m_line; // number of line in which token was gathered
    int m_idx; // column that token ends at
    TokenType m_type;
    std::string m_val;
    std::string m_TokenTypeToString() const;
    void m_AddCategory(std::string_view lex);
public:
    Token() {};
    Token(int _line, int _idx, std::string_view lex);
    Token(int _line, int _idx, TokenType type, std::string_view value): m_type(type), m_val(value), m_line(_line), m_idx(_idx) {};
    const TokenType type() const { return m_type; };
    const std::string value() const { return m_val; };
    std::string PrintFormat() const;   
};

