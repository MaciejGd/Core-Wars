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
protected:
    int m_val;
    // variable needed for creating instruction during parsing
    bool m_first_param_set = false; 
};