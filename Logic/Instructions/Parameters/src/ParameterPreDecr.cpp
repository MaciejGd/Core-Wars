#include "ParameterPreDecr.h"
#include "Arena.h"
#include "Instruction.h"

std::unique_ptr<CParameter> CParameterPreDecr::clone() const
{
    return std::unique_ptr<CParameter>(new CParameterPreDecr{*this});
}

void CParameterPreDecr::EvaluateParameter(int pc)
{
    m_FoldPointer();
    CArena& arena = CArena::GetInstance();
    int current_b_value = arena[pc+m_pointer]->GetBParamValue();
    // when we go out of bounds, we need to "jump" to the end of array
    arena[pc + m_pointer]->SetBParamValue((current_b_value + ARENA_SIZE - 1) % ARENA_SIZE);
    // assign pointers in indirect manner
    m_IndirectPointerAssign(pc);
}