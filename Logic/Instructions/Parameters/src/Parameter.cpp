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
    m_val = val; // actually we will handle negative values later
    // we should turn negative values to positive by wrapping around
    //m_val = (val + ARENA_SIZE) % ARENA_SIZE; 
}

const bool CParameter::ValueIsSet() const 
{
    return m_first_param_set;
}

void CParameter::m_FoldPointer()
{
    m_pointer = CArena::Fold(m_val);
}

void CParameter::m_IndirectPointerAssign(int pc)
{
    // get reference to singleton arena instance
    CArena& arena = CArena::GetInstance();
    // get B values from instructions pointed by pointer
    int indirect_ptr = arena[pc + m_pointer]->GetBParamValue();
    // set new values of ptrs
    m_pointer = CArena::Fold(m_pointer + indirect_ptr);
}
