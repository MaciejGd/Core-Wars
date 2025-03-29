#include "ParameterImmediate.h"

std::unique_ptr<CParameter> CParameterImmediate::clone() const
{
    return std::unique_ptr<CParameter>(new CParameterImmediate{*this});
}

void CParameterImmediate::EvaluateParameter(int pc)
{
    m_RP = m_WP = 0;
}
