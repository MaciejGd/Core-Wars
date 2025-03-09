#pragma once

#include "Parameter.h"
#include "logger.h"

#include <memory>

class CArena;


/// @brief Abstract class representing operations possible in Redcode
class COperation {
public:
    COperation(CParameter* first_arg, CParameter* second_arg);
    // setters
    void SetFirstArg(CParameter* first_arg);
    void SetSecondArg(CParameter* second_arg);
    // getters
    const CParameter* GetFirstArg() const { return m_first_arg.get(); };
    const CParameter* GetSecondArg() const { return m_second_arg.get(); };
    
    virtual void evaluate(CArena& arena) = 0;
    // DEBUG
    void debugPrint() { LOG_ERR("Inside operation"); } 
private:

protected:
    std::unique_ptr<CParameter> m_first_arg;
    std::unique_ptr<CParameter> m_second_arg;
};