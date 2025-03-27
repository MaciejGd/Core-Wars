#pragma once

#include "Parameter.h"


class CParameterPostInc : public CParameter {
public:
    CParameterPostInc() = default;
    CParameterPostInc(int val): CParameter(val) {}
private:

protected:
    const std::string m_id = "PostInc";
};