#pragma once

#include "Instruction.h"
#include "Parser.h"
#include "Lexer.h"

#include <vector>
#include <string>

class CCodeBuilder {
public:
    CCodeBuilder() = default;
    CCodeBuilder(std::string file_name);

    private:
    std::vector<CInstruction> m_instructions;
    CLexer m_lexer;
    std::string m_file_name;

    void m_ProcessProgramFile();
};