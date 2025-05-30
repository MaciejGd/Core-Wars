#pragma once

#include "Parameter.h"
#include "Operation.h"
#include <memory>



/// Class representing single instruction to be placed on game arena
/// Consists of:
/// - COperation: operation that instruction executes
/// - two CParameter: parameters to instruction
class CInstruction {
public:
    CInstruction() = default;
    /// @brief Copy constructor for CInstruction
    /// @param other instruction to be copied
    CInstruction(const CInstruction& other);
    CInstruction(CInstruction&& other);

    CInstruction& operator=(const CInstruction& other);
    CInstruction& operator=(CInstruction&& other);

    /// @brief Function that creates parameter during parsing of RedCode program
    /// @param param pointer to parameter of proper type
    bool CreateParameter(std::unique_ptr<CParameter> param);

    /// @brief Function that sets value for parameter, created during parsing of RedCode program
    /// @param value value of the parameter to be set
    bool CreateParamValue(int value);

    /// @brief Set A parameter of the instruction
    /// @param param pointer to be set as the A parameter of the instruction
    void SetAParameter(std::unique_ptr<CParameter> param);

    /// @brief Set value of the A parameter of the instruction
    /// @param value integer representing value of the parameter
    /// @return boolean indicating if operation succeeded 
    bool SetAParamValue(int value);

    /// @brief Set B parameter of the instruction
    /// @param param pointer to be set as the B parameter of the instruction
    void SetBParameter(std::unique_ptr<CParameter> param);

    /// @brief Set value of the A parameter of the instruction
    /// @param value integer representing value of the parameter
    /// @return boolean indicating if operation succeeded 
    bool SetBParamValue(int value);

    /// @brief Set operation of the instruction
    /// @param operation pointer to the operation to be set in instruction 
    void SetOperation(std::unique_ptr<COperation> operation);

    /// @brief Set modifier for instruction's operation
    /// @param modifier type of modifier to be set
    /// @return boolean indicating if operation succeeded
    bool SetModifier(ModifierType modifier);


    /// @brief Switch default modifier with respective value for set operation
    void DeduceDefaultModifier();

    /// @brief Add default B parameter if it has not been provided during creation
    void FinishInstructionSetup();

    /// @brief Debug function for printing instruction
    std::string PrintInstruction() const;

    const int GetAParamValue() const { return m_A_param->GetValue(); };
    const int GetBParamValue() const { return m_B_param->GetValue(); };

    /// @brief Static function for creating default DAT #0, #0 instruction
    /// @return unique ptr to DAT #0, #0 instruction created
    static std::unique_ptr<CInstruction> CreateDefaultInstruction();    

    /// @brief Evaluates parameters and runs operation
    /// @param pc current memory cell executed
    /// @param modified_cell index of modified cell, if there is
    /// @return boolean indicating status of execution operation
    InstructionResult Execute(int& pc, int& modified_cell);

    // DEBUG PURPOSES!!! shouldnt be needed in code
    const std::unique_ptr<CParameter>& GetAParam() const { return m_A_param; };
    const std::unique_ptr<CParameter>& GetBParam() const { return m_B_param; };
    const ModifierType GetModifier() const { return m_operation->GetModifier(); }
private:
    bool m_SetParamValue(std::unique_ptr<CParameter>& arg, int value);

    std::unique_ptr<CParameter> m_A_param;
    std::unique_ptr<CParameter> m_B_param;
    std::unique_ptr<COperation> m_operation;
};