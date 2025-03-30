#include "ParameterImmediate.h"

std::unique_ptr<CParameter> CParameterImmediate::clone() const
{
    return std::unique_ptr<CParameter>(new CParameterImmediate{*this});
}

void CParameterImmediate::EvaluateParameter(int pc)
{
    m_pointer = 0;
}
