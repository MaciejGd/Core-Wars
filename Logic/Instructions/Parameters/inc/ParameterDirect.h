#pragma once

#include "Parameter.h"


class CParameterDirect : public CParameter {
public:
    CParameterDirect() = default;
    CParameterDirect(int val): CParameter(val) {}
private:

protected:
    const std::string m_id = "Direct";
};