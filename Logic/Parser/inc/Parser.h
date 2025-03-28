#pragma once

#include "Lexer.h"
#include "ASTNode.h"
#include "Instruction.h"

#include <vector>


/// @brief Class checking if grammar rules of RedCode language 
///
/// has been met. Analyze tokens retrieved during the process of lexical
///
/// analysis and builts initial instructions for a player based on that.
class CParser {
public:
    /// @brief Function responsible for parsing input RedCode program and building initial instructions based on that
    /// @param tokens 2D vector of tokens, retrieved during lexing stage
    /// @param instructions vector of instructions, to be filled with parsed instructions
    /// @return boolean value indicating result of parsing a file
    static bool ParseFile(TokenContainer& tokens, std::vector<std::unique_ptr<CInstruction>>& instructions);
private:
    /// @brief Parse one row of tokens
    /// @param tokens_row vector of Tokens to be parsed
    /// @param instructions unique_ptr of CInstruction, to be modified during parsing of the line
    /// @return boolean indicating result of parsing a line
    static bool m_ParseLine(const std::vector<Token>& tokens_row, std::unique_ptr<CInstruction>& instruction);

    /// @brief Removes labels and place relative numbers in its place
    /// @param tokens two dimensional array of tokens
    /// @return bool indicating status removing labels operation
    static bool m_RemoveLabels(TokenContainer& tokens);


    /// @brief Recursive function for traversing Abstract Syntax Tree
    /// @param tokens queue of tokens to be parsed
    /// @param nodes stack that next nodes will be pushed to
    /// @param instruction pointer to instruction to be modified during parsing line
    /// @return boolean indicating result of the parsing
    static bool m_TraverseAST(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes,
                        std::unique_ptr<CInstruction>& instruction);
};
