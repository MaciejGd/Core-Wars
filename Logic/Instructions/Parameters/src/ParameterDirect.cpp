#include "ParameterDirect.h"
#include "Arena.h"

std::unique_ptr<CParameter> CParameterDirect::clone() const
{
    return std::unique_ptr<CParameter>(new CParameterDirect{*this});
}

void CParameterDirect::EvaluateParameter(int pc)
{
    // inherited from CParameter
    m_FoldPointers();
}
