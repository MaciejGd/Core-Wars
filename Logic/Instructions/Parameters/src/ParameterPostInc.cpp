#include "ParameterPostInc.h"
#include "Arena.h"
#include "Instruction.h"

void CParameterPostInc::EvaluateParameter(int pc)
{
    m_FoldPointers();
    // pip: post increment pointer
    // address that should be incremented after assigning RP and WP proper values
    int pip = pc + m_WP;
    // assign RP and WP in indirect manner 
    m_IndirectPointersAssign(pc);

    // increment B param pointed by pip afterwards
    CArena& arena = CArena::GetInstance();
    int current_b_value = arena[pip]->GetBParamValue(); 
    arena[pip]->SetBParamValue(current_b_value + 1);
}
