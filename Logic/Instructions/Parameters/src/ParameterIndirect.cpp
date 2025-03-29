#include "ParameterIndirect.h"
#include "Arena.h"

void CParameterIndirect::EvaluateParameter(int pc)
{
    m_FoldPointers();
    m_IndirectPointersAssign(pc);
}
