#include "OperationDJN.h"
#include "Arena.h"
#include "Instruction.h"

COperationDJN::COperationDJN()
{
    m_name = "DJN";
}

std::unique_ptr<COperation> COperationDJN::clone() const
{
    return std::unique_ptr<COperation>(new COperationDJN{*this});
}

InstructionResult COperationDJN::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    CArena& arena = CArena::GetInstance();
    int b_pointer = B_param->GetPointer();
    int a_pointer = A_param->GetPointer();
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
    return InstructionResult::PASS;
}
