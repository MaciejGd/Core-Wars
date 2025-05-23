#include "OperationADD.h"
#include "Arena.h"
#include "Instruction.h"
#include "logger.h"
#include "DefaultModSetterArithm.h"

COperationADD::COperationADD()
{
    // set name and default modifier setter
    m_name = "ADD";
    m_def_modifier = std::make_unique<CDefaultModSetterArithm>();
}

std::unique_ptr<COperation> COperationADD::clone() const
{
    return std::unique_ptr<COperation>(new COperationADD{*this});
}

InstructionResult COperationADD::Execute(int a_pointer, int b_pointer, int &pc, int &modified_cell)
{
    CArena& arena = CArena::GetInstance();
    

    auto& IRB = arena[pc + b_pointer];
    auto& IRA = arena[pc + a_pointer];

    auto IRB_BNUM = IRB->GetBParamValue();
    auto IRB_ANUM = IRB->GetAParamValue();
    auto IRA_BNUM = IRA->GetBParamValue();
    auto IRA_ANUM = IRA->GetAParamValue();

    switch (m_modifier)
    {
        case A:
            // set value A IRB to value A of IRB + value A of IRA
            IRB->SetAParamValue((IRB_ANUM + IRA_ANUM) % ARENA_SIZE);
            break;
        case B:
            IRB->SetBParamValue((IRB_BNUM + IRA_BNUM) % ARENA_SIZE);
            break;
        case AB:
            IRB->SetBParamValue((IRB_BNUM + IRA_ANUM) % ARENA_SIZE);
            break;
        case BA:
            IRB->SetAParamValue((IRB_ANUM + IRA_BNUM) % ARENA_SIZE);
            break;
        case X:
            IRB->SetAParamValue((IRB_BNUM + IRA_ANUM) % ARENA_SIZE);
            IRB->SetBParamValue((IRB_ANUM + IRA_BNUM) % ARENA_SIZE);
            break;  
        case F:
        case I:
            IRB->SetAParamValue((IRB_ANUM + IRA_ANUM) % ARENA_SIZE);
            IRB->SetBParamValue((IRB_BNUM + IRA_BNUM) % ARENA_SIZE);
            break;
        default: 
            LOG_ERR("Undefined parameter in {}", m_name);
            return InstructionResult::FAIL;
    }
    // wrap modified cell
    modified_cell = (((pc + b_pointer) % ARENA_SIZE) + ARENA_SIZE) % ARENA_SIZE;
    pc = (pc + 1) % ARENA_SIZE;
    return InstructionResult::PASS;
}
