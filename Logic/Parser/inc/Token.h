#pragma once

#include <array>
#include <string>
#include <iostream>
#include <string_view>
#include <algorithm>
#include <vector>

///
/// Enumeration type representing types of tokens 
/// identified during lexical analysis
/// 
/// Token types are:
///
/// - OPERATIONS: operation from RedCode lang, ex. mov, dat, etc.
/// - SEPARATOR: separators like , or ) ( ... TODO
/// - LABEL: labels that user can name lines of code with 
/// - MODIFIERS: modifiers to operation in RedCode, ex. .a, .ab, etc.
/// - ADDRESS_MODE: address modes available in RedCode, ex. #, $, etc.
/// - ARITHM_OPS: arithmetic operators, that can be used in params declaration
/// - NUMERICAL_VAL: numerical values indicating memory regions
/// - END_LINE: indicates end of line, and is pushed at the end of every token row lexed 
///
enum TokenType {
    OPERATIONS,
    SEPARATOR,
    LABEL,
    MODIFIERS,
    ADDRESS_MODE,
    ARITHM_OPS,
    NUMERICAL_VAL,
    END_LINE
};

// possible modifiers in RedCode language
constexpr std::array<std::string, 7> tkn_modifiers = {".a", ".b", ".ab", ".ba", ".f", ".x", ".i"};
// possible operations in RedCode language
constexpr std::array<std::string, 17> tkn_operations = {"dat", "mov", "add", "sub", "mul", "div", "mod", 
                    "jmp", "jmz", "jmn", "djn", "spl", "cmp", "seq", "org", "equ", "end"};
// five basic arithmetic operations
constexpr std::array<char, 5> tkn_ar_ops = {'+', '-', '/', '*', '%'}; 
// semicolon indicates comment and will be skipped during lexing
constexpr char tkn_comment = ';'; 
constexpr std::array<char, 3> tkn_separators = {',', '(', ')'};
// address modes in RedCode language
constexpr std::array<char, 7> tkn_address_modes = {'#', '$', '<', '>', '{', '}', '@'};


/// @brief Helper function for checking if element is present in array
/// @tparam T type of an array and searched element
/// @tparam N size of an array
/// @param arr array to perform search on
/// @param value value to be searched
/// @return true if element found, false otherwise
template<typename T, size_t N>
bool findInArray(const std::array<T, N>& arr, T value) 
{
    if (std::find(arr.begin(), arr.end(), value) != arr.end()) 
    {
        return true;
    }
    return false;
};

///
/// Class representing single lexical unit of RedCode code
/// 
/// Token is described by four main attributes:
/// 1. line - line of token's occurence
/// 2. idx - column of token's ending
/// 3. type - type of Token, described in TokenType enum
/// 4. value - string representing part of text, that token describes
/// 
class Token {
public:
    Token() {};
    Token(int _line, int _idx, std::string_view lex);
    Token(int _line, int _idx, TokenType type, std::string_view value):
         m_type(type), m_val(value), m_line(_line), m_idx(_idx) {};

    // setters
    void SetType(TokenType type) { m_type = type; };
    void SetValue(std::string_view value) { m_val = value; };
    // getters
    const TokenType type() const { return m_type; };
    const std::string value() const { return m_val; };
    const int line() const { return m_line; };
    const int idx() const { return m_idx; };

    /// @brief Function helping in debug, showing Token's 
    /// params in form of formatted string
    /// @return string consisting Token's params
    std::string PrintFormat() const;   


    /// @brief Turn token's type to string and return it
    /// @return string representing token's type
    std::string TokenTypeToString() const;

private:
    int m_line; // number of line in which token was gathered
    int m_idx; // column that token ends at
    TokenType m_type;
    std::string m_val;
    void m_AddCategory(const std::string& lex);
};

/// @brief function printing lexed line of tokens, for debug purposes
/// @param line line of tokens
inline void PrintTokensLine(std::vector<Token>& line)
{
    for (auto &x : line)
    {
        std::cout << x.value() << "type: " << x.TokenTypeToString() << "|";
    }
    std::cout << std::endl;
}