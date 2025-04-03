#include "OperationDIV.h"
#include "Arena.h"
#include "Instruction.h"
#include "Parameter.h"
#include "logger.h"

COperationDIV::COperationDIV()
{
    m_name = "DIV";
}

std::unique_ptr<COperation> COperationDIV::clone() const
{
    return std::unique_ptr<COperation>(new COperationDIV{*this});
}

bool COperationDIV::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    LOG_DBG("Executing {}.{} in memory cell {}", m_name, ModifierToString(m_modifier), pc);
    CArena& arena = CArena::GetInstance();
    int a_pointer = A_param->GetPointer();
    int b_pointer = B_param->GetPointer();

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
                return false;
            }
            IRB->SetAParamValue(IRB_ANUM / IRA_ANUM);
            break;
        case B:
            if (IRA_BNUM == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return false;
            }
            IRB->SetBParamValue(IRB_BNUM / IRA_BNUM);
            break;
        case AB:
            if (IRA_BNUM == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return false;
            }
            IRB->SetBParamValue(IRB_ANUM / IRA_BNUM);
            break;
        case BA:
            if (IRA_ANUM == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return false;
            }
            IRB->SetAParamValue(IRB_BNUM / IRA_ANUM);
            break;
        case X:
            if (IRA_ANUM == 0 || IRA_BNUM == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return false;
            }
            IRB->SetAParamValue(IRB_BNUM / IRA_ANUM);
            IRB->SetBParamValue(IRB_ANUM / IRA_BNUM);
            break;  
        case F:
        case I:
            if (IRA_ANUM == 0 || IRA_BNUM == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return false;
            }
            IRB->SetAParamValue(IRB_ANUM / IRA_ANUM);
            IRB->SetBParamValue(IRB_BNUM / IRA_BNUM);
            break;
        default: 
            LOG_ERR("Undefined parameter in {}", m_name);
            return false;
    }
    pc = (pc + 1) % ARENA_SIZE;
    return true;
}
