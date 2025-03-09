#pragma once

enum ParamType {
    INDIRECT,
    DIRCET,
    IMMIDIATE,
    AUTOINC
};

class CParameter {
public:
    CParameter(int arg, ParamType type);
    const ParamType GetType() const { return m_type; }
    const int GetArg() const { return m_arg; }
private:
    int m_arg;
    ParamType m_type;

};