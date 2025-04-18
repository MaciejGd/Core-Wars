#include "OperationSUB.h"
#include "Arena.h"
#include "Instruction.h"
#include "logger.h"
#include "DefaultModSetterArithm.h"

COperationSUB::COperationSUB()
{
    m_name = "SUB";
    m_def_modifier = std::make_unique<CDefaultModSetterArithm>();
}

std::unique_ptr<COperation> COperationSUB::clone() const
{
    return std::unique_ptr<COperation>(new COperationSUB{*this});
}

InstructionResult COperationSUB::Execute(int a_pointer, int b_pointer, int &pc, int &modified_cell)
{
    CArena& arena = CArena::GetInstance();
    

    auto& IRB = arena[pc + b_pointer];
    auto& IRA = arena[pc + a_pointer];
    // we need to make copies of parameters, as modifying in place leads to bug in X modifier
    auto IRB_BNUM = IRB->GetBParamValue();
    auto IRB_ANUM = IRB->GetAParamValue();
    auto IRA_BNUM = IRA->GetBParamValue();
    auto IRA_ANUM = IRA->GetAParamValue();

    switch (m_modifier)
    {
        case A:
            // set value A IRB to value A of IRB + value A of IRA
            IRB->SetAParamValue(IRB_ANUM - IRA_ANUM);
            break;
        case B:
            IRB->SetBParamValue(IRB_BNUM - IRA_BNUM);
            break;
        case AB:
            IRB->SetBParamValue(IRB_BNUM - IRA_ANUM);
            break;
        case BA:
            IRB->SetAParamValue(IRB_ANUM - IRA_BNUM);
            break;
        case X:
            IRB->SetAParamValue(IRB_BNUM - IRA_ANUM);
            IRB->SetBParamValue(IRB_ANUM - IRA_BNUM);
            break;  
        case F:
        case I:
            IRB->SetAParamValue(IRB_ANUM - IRA_ANUM);
            IRB->SetBParamValue(IRB_BNUM - IRA_BNUM);
            break;
        default: 
            LOG_ERR("Undefined parameter in {}", m_name);
            return InstructionResult::FAIL;
    }
    // update modified cell as it was modified
    modified_cell = (((pc + b_pointer) % ARENA_SIZE) + ARENA_SIZE) % ARENA_SIZE;
    pc = (pc + 1) % ARENA_SIZE;
    return InstructionResult::PASS;
}
