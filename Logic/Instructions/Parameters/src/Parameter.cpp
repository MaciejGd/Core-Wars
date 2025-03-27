#include "Parameter.h"

CParameter::CParameter(int val): m_val(val)
{
    m_first_param_set = true;
}

void CParameter::SetValue(int val)
{
    m_first_param_set = true;
    m_val = val;
}

const bool CParameter::ValueIsSet() const 
{
    return m_first_param_set;
}
