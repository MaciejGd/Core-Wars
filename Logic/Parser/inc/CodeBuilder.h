#pragma once

#include "Instruction.h"
#include "Parser.h"
#include "Lexer.h"

#include <vector>
#include <string>

class CCodeBuilder {
public:
    CCodeBuilder() = default;

    void SetFileName(const std::string& file_name) { m_file_name = file_name; };
    bool ProduceInstructions(std::string_view file_name);
    
    std::vector<std::unique_ptr<CInstruction>>& GetInstructions() { return m_instructions; };
private:
    std::vector<std::unique_ptr<CInstruction>> m_instructions;
    CLexer m_lexer;
    std::string m_file_name;

    bool m_ProcessProgramFile();
    void m_DeduceDefaultModifiers();
};