#pragma once

#include <string>
#include <memory>

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

    const int GetValue() const { return m_val; }
    virtual const std::string Identify() const { return ""; };
    void SetValue(int value);
    const bool ValueIsSet() const;

    virtual void EvaluateParameter(int pc) = 0;
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