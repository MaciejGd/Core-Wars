#include "OperationMUL.h"
#include "Arena.h"
#include "Instruction.h"
#include "Parameter.h"
#include "logger.h"

COperationMUL::COperationMUL()
{
    m_name = "MUL";
}

std::unique_ptr<COperation> COperationMUL::clone() const
{
    return std::unique_ptr<COperation>(new COperationMUL{*this});
}

bool COperationMUL::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    LOG_DBG("Executing {}.{} in memory cell {}", m_name, ModifierToString(m_modifier), pc);
    CArena& arena = CArena::GetInstance();
    int a_pointer = A_param->GetPointer();
    int b_pointer = B_param->GetPointer();

    auto& IRB = arena[pc + b_pointer];
    auto& IRA = arena[pc + a_pointer];

    switch (m_modifier)
    {
        case A:
            // set value A IRB to value A of IRB + value A of IRA
            IRB->SetAParamValue((IRB->GetAParamValue() * IRA->GetAParamValue()) % ARENA_SIZE);
            break;
        case B:
            IRB->SetBParamValue((IRB->GetBParamValue() * IRA->GetBParamValue()) % ARENA_SIZE);
            break;
        case AB:
            IRB->SetBParamValue((IRB->GetAParamValue() * IRA->GetBParamValue()) % ARENA_SIZE);
            break;
        case BA:
            IRB->SetAParamValue((IRB->GetBParamValue() * IRA->GetAParamValue()) % ARENA_SIZE);
            break;
        case X:
            IRB->SetAParamValue((IRB->GetBParamValue() * IRA->GetAParamValue()) % ARENA_SIZE);
            IRB->SetBParamValue((IRB->GetAParamValue() * IRA->GetBParamValue()) % ARENA_SIZE);
            break;  
        case F:
        case I:
            IRB->SetAParamValue((IRB->GetAParamValue() * IRA->GetAParamValue()) % ARENA_SIZE);
            IRB->SetBParamValue((IRB->GetBParamValue() * IRA->GetBParamValue()) % ARENA_SIZE);
            break;
        default: 
            LOG_ERR("Undefined parameter in {}", m_name);
            return false;
    }
    pc = (pc + 1) % ARENA_SIZE;
    return true;
}
