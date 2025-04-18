#include "OperationDJN.h"
#include "Arena.h"
#include "Instruction.h"
#include "DefaultModSetterJump.h"

COperationDJN::COperationDJN()
{
    m_name = "DJN";
    m_def_modifier = std::make_unique<CDefaultModSetterJump>();
}

std::unique_ptr<COperation> COperationDJN::clone() const
{
    return std::unique_ptr<COperation>(new COperationDJN{*this});
}

InstructionResult COperationDJN::Execute(int a_pointer, int b_pointer, int &pc, int &modified_cell)
{
    CArena& arena = CArena::GetInstance();
    
    // retrieve numbers from instruction pointed to by B param
    auto &target = arena[pc + b_pointer];

    switch (m_modifier)
    {
        case A:
        [[fallthrough]];
        case BA:
            // param probably shouldnt be mod in here
            target->SetAParamValue(target->GetAParamValue() -1);
            //target->SetAParamValue((target->GetAParamValue() + ARENA_SIZE - 1) % ARENA_SIZE);
            if (target->GetAParamValue() !=  0)
            {
                pc = (pc + a_pointer) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc + 1) % ARENA_SIZE;
            }
            break;
        case B:
        [[fallthrough]];
        case AB:
            target->SetBParamValue(target->GetBParamValue() -1);
            //target->SetBParamValue((target->GetBParamValue() + ARENA_SIZE - 1) % ARENA_SIZE);
            if (target->GetBParamValue() !=  0)
            {
                pc = (pc + a_pointer) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc + 1) % ARENA_SIZE;
            }
            break;
        case F:
        [[fallthrough]];
        case X:
        [[fallthrough]];
        case I:
            // decrement value of both A and B and check if any got zero
            target->SetAParamValue(target->GetAParamValue() -1);
            target->SetBParamValue(target->GetBParamValue() -1);
            // target->SetAParamValue((target->GetAParamValue() + ARENA_SIZE -1) % ARENA_SIZE);
            // target->SetBParamValue((target->GetBParamValue() + ARENA_SIZE -1) % ARENA_SIZE);
            if (target->GetAParamValue() != 0 || target->GetAParamValue() != 0)
            {
                pc = (pc + a_pointer) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc + 1) % ARENA_SIZE;
            }
        default:
            return InstructionResult::FAIL;
    }
    // update modified cell as it was modified
    modified_cell = (((pc + b_pointer) % ARENA_SIZE) + ARENA_SIZE) % ARENA_SIZE;
    return InstructionResult::PASS;
}
