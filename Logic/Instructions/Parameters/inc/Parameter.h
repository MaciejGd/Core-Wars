#pragma once

#include <string>

class CParameter {
public:
    CParameter() = default;
    CParameter(int val);
    const int GetValue() const { return m_val; }
    virtual const std::string Identify() const { return "Empty"; };
    void SetValue(int value);
    const bool ValueIsSet() const;

    virtual void EvaluateParameter(int pc) = 0;
    const int GetReadPointer() const { return m_WP; };
    const int GetWritePointer() const { return m_WP; };

protected:
    int m_RP; // readpointer of the parameter
    int m_WP; // writepointer of the parameter
    int m_val;
    // variable needed for creating instruction during parsing
    bool m_first_param_set = false; 

    /// @brief Function for folding parameters as they can exceed limit of read-write range
    void m_FoldPointers();

    /// @brief Function for setting RP and WP as direct ()
    void m_IndirectPointersAssign(int pc);
};