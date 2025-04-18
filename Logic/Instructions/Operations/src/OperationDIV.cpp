#include "OperationDIV.h"
#include "Arena.h"
#include "Instruction.h"
#include "logger.h"
#include "DefaultModSetterArithm.h"

COperationDIV::COperationDIV()
{
    m_name = "DIV";
    m_def_modifier = std::make_unique<CDefaultModSetterArithm>();
}

std::unique_ptr<COperation> COperationDIV::clone() const
{
    return std::unique_ptr<COperation>(new COperationDIV{*this});
}

InstructionResult COperationDIV::Execute(int a_pointer, int b_pointer, int &pc, int &modified_cell)
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
            if (IRA_ANUM == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return InstructionResult::FAIL;
            }
            IRB->SetAParamValue(IRB_ANUM / IRA_ANUM);
            break;
        case B:
            if (IRA_BNUM == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return InstructionResult::FAIL;
            }
            IRB->SetBParamValue(IRB_BNUM / IRA_BNUM);
            break;
        case AB:
            if (IRA_ANUM == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return InstructionResult::FAIL;
            }
            IRB->SetBParamValue(IRB_BNUM / IRA_ANUM);
            break;
        case BA:
            if (IRA_BNUM == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return InstructionResult::FAIL;
            }
            IRB->SetAParamValue(IRB_ANUM / IRA_BNUM);
            break;
        case X:
            if (IRA_ANUM == 0 || IRA_BNUM == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return InstructionResult::FAIL;
            }
            IRB->SetAParamValue(IRB_BNUM / IRA_ANUM);
            IRB->SetBParamValue(IRB_ANUM / IRA_BNUM);
            break;  
        case F:
        case I:
            if (IRA_ANUM == 0 || IRA_BNUM == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return InstructionResult::FAIL;
            }
            IRB->SetAParamValue(IRB_ANUM / IRA_ANUM);
            IRB->SetBParamValue(IRB_BNUM / IRA_BNUM);
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
