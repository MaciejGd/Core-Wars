#pragma once

#include "Parameter.h"


class CParameterImmidiate : public CParameter {
public:
    CParameterImmidiate() = default;
    CParameterImmidiate(int val): CParameter(val) {}
protected:
    const std::string m_id = "Immidiate";
};