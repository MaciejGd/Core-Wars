#pragma once

#include <vector>
#include <string_view>

#include <Token.h>

using TokenContainer = std::vector<std::vector<Token>>;

/// Class responsible for lexical analysis of input RedCode file.
/// Its main task is to create TokenContainer filled with tokens retrieved
/// during analysis, that we can feed parser with.
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