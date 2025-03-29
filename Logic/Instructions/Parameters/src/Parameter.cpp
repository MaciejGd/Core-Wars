#include "Parameter.h"
#include "Arena.h"
#include "Instruction.h"

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

void CParameter::m_FoldPointers()
{
    m_RP = CArena::Fold(m_val);
    m_WP = CArena::Fold(m_val);
}

void CParameter::m_IndirectPointersAssign(int pc)
{
    // get reference to singleton arena instance
    CArena& arena = CArena::GetInstance();
    // get B values from instructions pointed by RP and WP
    int indirect_read_ptr = arena[pc + m_RP]->GetBParamValue();
    int indirect_write_ptr = arena[pc + m_WP]->GetBParamValue();
    // set new values of ptrs
    m_RP = CArena::Fold(m_RP + indirect_read_ptr);
    m_WP = CArena::Fold(m_WP + indirect_write_ptr);
}
