#pragma once

#include "Parameter.h"
#include <memory>

class CInstruction {
public:
    /// @brief Function that creates parameter during parsing of RedCode program
    /// @param param pointer to parameter of proper type
    void CreateParameter(std::unique_ptr<CParameter> param);

    /// @brief Function that sets value for parameter, created during parsing of RedCode program
    /// @param value value of the parameter to be set
    void CreateParamValue(int value);
    void SetAParameter(std::unique_ptr<CParameter> param);
    void SetAParamValue(int value);
    void SetBParameter(std::unique_ptr<CParameter> param);
    void SetBParamValue(int value);
private:
    bool m_SetParamValue(std::unique_ptr<CParameter>& arg, int value);
    std::unique_ptr<CParameter> m_A_param;
    std::unique_ptr<CParameter> m_B_param;
};