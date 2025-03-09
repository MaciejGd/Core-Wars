#include "Operation.h"

COperation::COperation(CParameter *first_arg, CParameter *second_arg)
{
    m_first_arg.reset(std::move(first_arg));
    m_second_arg.reset(std::move(second_arg));
}

void COperation::SetFirstArg(CParameter* first_arg)
{
    m_first_arg.reset(std::move(first_arg));
}

void COperation::SetSecondArg(CParameter* second_arg)
{
    m_second_arg.reset(std::move(second_arg));
}
