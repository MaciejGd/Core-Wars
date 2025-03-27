#pragma once

#include <string>


class CParameter {
public:
    CParameter() = default;
    CParameter(int val);
    const int GetValue() const { return m_val; }
    virtual std::string Identify() { return m_id; };
    void SetValue(int value);
    const bool ValueIsSet() const;
protected:
    int m_val;
    // constant used for identifying instance of the class
    const std::string m_id;
    // variable needed for creating instruction during parsing
    bool m_first_param_set = false; 
};