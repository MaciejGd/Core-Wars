#pragma once

#include <string>
#include <memory>

/// Class representing parameter of the instruction.
/// Derived classes should implement EvaluateParameter method
/// which counts the pointer, basing on parameter value
class CParameter {
public:
    CParameter() = default;
    CParameter(int val);
    
    /// @brief copy contructor needed for MOV operation which copies instructions
    /// @param other parameter of instruction to be copied
    CParameter(const CParameter& other) = default;

    /// @brief Virtual function needed for copying Param object
    /// @return unique pointer to newly created object
    virtual std::unique_ptr<CParameter> clone() const = 0;

    /// @brief Count pointer basing on the pointer's value
    /// @param pc program counter of the player
    virtual void EvaluateParameter(int pc) = 0;

    /// @brief Value of the parameter getter
    /// @return value of the parameter
    const int GetValue() const { return m_val; }

    /// @brief Identify type of the parameter
    /// @return string indicating parameter's type
    virtual const std::string Identify() const { return ""; };

    /// @brief Value of the parameter setter
    /// @param value value to be set as parameter value
    void SetValue(int value);

    /// @brief Check if value for the parameter has been set
    /// @return boolean indicating if value for parameter has been set 
    const bool ValueIsSet() const;

    /// @brief Getter of the parameter's pointer
    /// @return parameter's pointer
    const int GetPointer() const { return m_pointer; };
protected:
    int m_val;
    int m_pointer;
    // variable needed for creating instruction during parsing
    bool m_first_param_set = false; 

    /// @brief Function for folding parameters as they can exceed limit of read-write range
    void m_FoldPointer();

    /// @brief Function for setting pointer as direct ()
    void m_IndirectPointerAssign(int pc);
};