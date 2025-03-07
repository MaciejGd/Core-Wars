#pragma once


#include "Arena.h"

class COperation {
public:
    COperation();
    // setters
    void SetFirstArg();
    void SetSecondArg();
    // getters
    const int GetFirstArg() const;
    const int GetSecondArg() const;
    
    void evaluate(Arena& arena);
private:

protected:
    int m_first_arg;
    int m_second_arg;
};