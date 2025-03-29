#pragma once

#include "Parameter.h"
#include "Operation.h"
#include <memory>

/// @brief Class representing single instruction to be placed on game arena
///
/// Consists of:
///
/// - COperation: operation that instruction executes
///
/// - two CParameter: parameters to instruction
class CInstruction {
public:
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

    /// @brief Debug function for printing instruction
    std::string PrintInstruction() const;

    const int GetAParamValue() const { return m_A_param->GetValue(); };
    const int GetBParamValue() const { return m_B_param->GetValue(); };

private:
    bool m_SetParamValue(std::unique_ptr<CParameter>& arg, int value);
    std::unique_ptr<CParameter> m_A_param;
    std::unique_ptr<CParameter> m_B_param;
    std::unique_ptr<COperation> m_operation;
};