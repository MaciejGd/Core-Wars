#pragma once

#include <vector>
#include <string_view>

#include <Token.h>

using TokenContainer = std::vector<std::vector<Token>>;
// TODO - turn it into a class with only static fields as Parser??? to consider that

/// @brief Singleton for creating token list from input file
class CLexer {
public:
    /// name of the file currently lexed
    inline static std::string s_file_name;

    /// @brief Function to lexically analyze input file
    /// @param file_path path to the file to be analyzed
    /// @return vector of tokens retrieved
    TokenContainer GetTokens(std::string_view file_path);
private:
    void m_TokenizeLine(const std::string& line, TokenContainer &tokens, int line_counter);
};