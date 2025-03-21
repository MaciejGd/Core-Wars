#pragma once

#include "Lexer.h"
// need to prepare some semantics for that

// what will be the dictionary for RedCode
// Program := Instruction + EndInstruction
// EndInstruction := EndInstruction 
// Instruction -> one line containing all elems
// InstructionNext -> either end of file or next instruction
// if every line is valid then whole file is valid so analyze line by line (tokens need to be in 2D array format)

// lexer, tokenizer, parser(), logic analyze(while creating proper object validate logic)

// how we want to parse input?
// analyze line by line or whole file and line as expression???



/// @brief Class checking if grammar rules of RedCode language 
/// has been met. Analyze tokens retrieved during the process of lexical
/// analysis.
class Parser {
public:
    /// @brief 
    /// @param tokens 
    void test_RemoveLables(TokenContainer& tokens);
private:
    void m_GenerateAst(TokenContainer& tokens);

    /// @brief Removes labels and place relative numbers in its place
    /// @param tokens two dimensional array of tokens
    /// @return bool indicating status removing labels operation
    bool m_RemoveLabels(TokenContainer& tokens);
};
