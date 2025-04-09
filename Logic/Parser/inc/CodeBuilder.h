#pragma once

#include "Instruction.h"
#include "Parser.h"
#include "Lexer.h"

#include <vector>
#include <string>

class CCodeBuilder {
public:
    CCodeBuilder() = default;
    /// Move constructor needed as we want to move players to vector 
    /// in main game loop initialization
    /// @param other CCodeBuilder object to be moved
    CCodeBuilder(CCodeBuilder&& other);

    // copy constructor should be deleted as class manage vector of unique_ptr
    CCodeBuilder(const CCodeBuilder& other) = delete;

    CCodeBuilder& operator=(const CCodeBuilder& other) = delete;
    CCodeBuilder& operator=(CCodeBuilder&& other);

    void SetFileName(const std::string& file_name) { m_file_name = file_name; };
    bool ProduceInstructions(std::string_view file_name);
    
    std::vector<std::unique_ptr<CInstruction>>& GetInstructions() { return m_instructions; };
    const int GetInstructionsAmount() const { return m_instructions.size(); }; 
private:
    std::vector<std::unique_ptr<CInstruction>> m_instructions;
    CLexer m_lexer;
    std::string m_file_name;

    bool m_ProcessProgramFile();
    void m_FinishInstructionsSetup();
};