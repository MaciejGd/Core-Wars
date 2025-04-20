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

    /// @brief Set file name to parse
    /// @param file_name name of the file to be parsed
    void SetFileName(const std::string& file_name) { m_file_name = file_name; };
    
    /// @brief Produce instructions based on path to the file 
    /// @param file_name name of the file to be analyzed
    /// @param offset offset of program counter in relation to first instruction
    /// @return boolean indicating status of the operation
    bool ProduceInstructions(std::string_view file_name, int& offset);
    
    /// @brief Return reference to CInstruction pointers vector
    /// @return reference to CInstruction vector created during parsing
    std::vector<std::unique_ptr<CInstruction>>& GetInstructions() { return m_instructions; };

    /// @brief Get amount of instructions created
    /// @return amount of instructions created
    const int GetInstructionsAmount() const { return m_instructions.size(); }; 

    /// @brief Get error message from the process of parsing warrior's code
    /// @return error message in form of string
    const std::string GetErrorMessage() const { return m_parser.GetErrorMessage(); };
private:
    std::vector<std::unique_ptr<CInstruction>> m_instructions;
    CLexer m_lexer;
    CParser m_parser;
    std::string m_file_name;

    bool m_ProcessProgramFile(int& offset);
    void m_FinishInstructionsSetup();
};