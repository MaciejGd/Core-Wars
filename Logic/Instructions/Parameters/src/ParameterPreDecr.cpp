#include "ParameterPreDecr.h"
#include "Arena.h"
#include "Instruction.h"

void CParameterPreDecr::EvaluateParameter(int pc)
{
    m_FoldPointers();
    CArena& arena = CArena::GetInstance();
    int current_b_value = arena[pc+m_WP]->GetBParamValue();
    // when we go out of bounds, we need to "jump" to the end of array
    arena[pc + m_WP]->SetBParamValue((current_b_value + ARENA_SIZE - 1) % ARENA_SIZE);
    // assign pointers in indirect manner
    m_IndirectPointersAssign(pc);
}