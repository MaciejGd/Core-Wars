#pragma once

#include "Parameter.h"


class CParameterIndirect : public CParameter {
public:
    CParameterIndirect() = default;
    CParameterIndirect(int val): CParameter(val) {}
private:

protected:
    const std::string m_id = "Indirect";
};