#include "ParameterIndirect.h"
#include "Arena.h"

std::unique_ptr<CParameter> CParameterIndirect::clone() const
{
    return std::unique_ptr<CParameter>(new CParameterIndirect{*this});
}

void CParameterIndirect::EvaluateParameter(int pc)
{
    m_FoldPointers();
    m_IndirectPointersAssign(pc);
}
