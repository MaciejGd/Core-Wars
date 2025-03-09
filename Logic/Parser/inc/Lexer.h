#pragma once

#include <vector>
#include <string_view>

#include <Token.h>


/// @brief Singleton for creating token list from input file
class Lexer {
public:
    static Lexer* GetInstance();
    /// @brief Function to lexically analyze input file
    /// @param file_path path to the file to be analyzed
    /// @return vector of tokens retrieved
    const std::vector<Token> GetTokens(std::string_view file_path);
private:
    Lexer() {};
    static Lexer* m_instance;
    
    void m_TokenizeLine(const std::string& line, std::vector<Token> &tokens);
};