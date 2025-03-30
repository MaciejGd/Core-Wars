#include "OperationMOD.h"
#include "Arena.h"
#include "Instruction.h"
#include "Parameter.h"
#include "logger.h"

COperationMOD::COperationMOD()
{
    m_name = "MOD";
}

std::unique_ptr<COperation> COperationMOD::clone() const
{
    return std::unique_ptr<COperation>(new COperationMOD{*this});
}

bool COperationMOD::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    LOG_DBG("Executing {}.{} in memory cell {}", m_name, ModifierToString(m_modifier), pc);
    CArena& arena = CArena::GetInstance();
    int a_pointer = A_param->GetPointer();
    int b_pointer = B_param->GetPointer();

    auto& IRB = arena[pc + b_pointer];
    auto& IRA = arena[pc + a_pointer];

    int IRA_A_Param = IRA->GetAParamValue();
    int IRA_B_Param = IRA->GetBParamValue();

    switch (m_modifier)
    {
        case A:
            // set value A IRB to value A of IRB + value A of IRA
            if (IRA_A_Param == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return false;
            }
            IRB->SetAParamValue((IRB->GetAParamValue() % IRA->GetAParamValue()));
            break;
        case B:
            if (IRA_B_Param == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return false;
            }
            IRB->SetBParamValue((IRB->GetBParamValue() % IRA->GetBParamValue()));
            break;
        case AB:
            if (IRA_B_Param == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return false;
            }
            IRB->SetBParamValue((IRB->GetAParamValue() % IRA->GetBParamValue()));
            break;
        case BA:
            if (IRA_A_Param == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return false;
            }
            IRB->SetAParamValue((IRB->GetBParamValue() % IRA->GetAParamValue()));
            break;
        case X:
            if (IRA_A_Param == 0 || IRA_B_Param == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return false;
            }
            IRB->SetAParamValue((IRB->GetBParamValue() % IRA->GetAParamValue()));
            IRB->SetBParamValue((IRB->GetAParamValue() % IRA->GetBParamValue()));
            break;  
        case F:
        case I:
            if (IRA_A_Param == 0 || IRA_B_Param == 0) 
            {
                LOG_ERR("Trying to divide by 0");
                return false;
            }
            IRB->SetAParamValue((IRB->GetAParamValue() % IRA->GetAParamValue()));
            IRB->SetBParamValue((IRB->GetBParamValue() % IRA->GetBParamValue()));
            break;
        default: 
            LOG_ERR("Undefined parameter in {}", m_name);
            return false;
    }
    pc = (pc + 1) % ARENA_SIZE;
    return true;
}
