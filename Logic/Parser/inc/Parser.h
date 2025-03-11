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



class Parser {
public:

private:
    void GenerateAst(TokenContainer tokens);
}
