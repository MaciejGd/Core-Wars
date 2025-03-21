#pragma once

#include <vector>
#include <string_view>

#include <Token.h>

using TokenContainer = std::vector<std::vector<Token>>;


/// @brief Singleton for creating token list from input file
class Lexer {
public:
    /// name of the file currently lexed
    inline static std::string s_file_name;

    static Lexer* GetInstance();
    /// @brief Function to lexically analyze input file
    /// @param file_path path to the file to be analyzed
    /// @return vector of tokens retrieved
    TokenContainer GetTokens(std::string_view file_path);
private:
    Lexer() {};
    static Lexer* m_instance;
    
    void m_TokenizeLine(const std::string& line, TokenContainer &tokens, int line_counter);
};