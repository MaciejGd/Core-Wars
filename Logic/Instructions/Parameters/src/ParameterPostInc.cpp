#include "ParameterPostInc.h"
#include "Arena.h"
#include "Instruction.h"

std::unique_ptr<CParameter> CParameterPostInc::clone() const
{
    return std::unique_ptr<CParameter>(new CParameterPostInc{*this});
}

void CParameterPostInc::EvaluateParameter(int pc)
{
    m_FoldPointer();
    // pip: post increment pointer
    // address that should be incremented after assigning pointer the proper values
    int pip = pc + m_pointer;
    // assign pointer in indirect manner 
    m_IndirectPointerAssign(pc);

    // increment B param pointed by pip afterwards
    CArena& arena = CArena::GetInstance();
    int current_b_value = arena[pip]->GetBParamValue(); 
    arena[pip]->SetBParamValue(current_b_value + 1);
}
