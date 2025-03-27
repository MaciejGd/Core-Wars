#pragma once

#include "Parameter.h"


class CParameterPreDecr : public CParameter {
public:
    CParameterPreDecr() = default;
    CParameterPreDecr(int val): CParameter(val) {}
private:

protected:
    const std::string m_id = "PreDecr";
};