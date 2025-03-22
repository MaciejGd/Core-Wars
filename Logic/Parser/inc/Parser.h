#pragma once

#include "Lexer.h"
#include "ASTNode.h"
#include <vector>


/// @brief Class checking if grammar rules of RedCode language 
/// has been met. Analyze tokens retrieved during the process of lexical
/// analysis.
class Parser {
public:
    /// @brief 
    /// @param tokens 
    void test_RemoveLables(TokenContainer& tokens);

    /// @brief Function responsible for parsing input RedCode program
    /// @param tokens 2D vector of tokens, retrieved during lexing stage
    /// @return boolean value indicating result of parsing a file
    bool ParseFile(TokenContainer& tokens);
private:
    /// @brief Parse one row of tokens
    /// @param tokens_row vector of Tokens to be parsed
    /// @return boolean indicating result of parsing a line
    bool m_ParseLine(const std::vector<Token>& tokens_row);

    /// @brief Removes labels and place relative numbers in its place
    /// @param tokens two dimensional array of tokens
    /// @return bool indicating status removing labels operation
    bool m_RemoveLabels(TokenContainer& tokens);


    /// @brief Recursive function for traversing Abstract Syntax Tree
    /// @param tokens queue of tokens to be parsed
    /// @param nodes stack that next nodes will be pushed to
    /// @return boolean indicating result of the parsing
    bool m_TraverseAST(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes);
};
