#include "OperationJMZ.h"
#include "Parameter.h"
#include "Arena.h"
#include "Instruction.h"
#include "logger.h"

COperationJMZ::COperationJMZ()
{
    m_name = "JMZ";
}

std::unique_ptr<COperation> COperationJMZ::clone() const
{
    return std::unique_ptr<COperation>(new COperationJMZ{*this});
}

bool COperationJMZ::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    LOG_DBG("Executing {}.{} in memory cell {}", m_name, ModifierToString(m_modifier), pc);
    CArena& arena = CArena::GetInstance(); // TODO turn it into a macro

    int WPB = B_param->GetWritePointer();
    int RPA = A_param->GetReadPointer();
    int RPB = B_param->GetReadPointer();
    // A number of instruction pointed by B param
    int IRB_ANUM = arena[pc+RPB]->GetAParamValue();
    // B number of instruction pointed by B param
    int IRB_BNUM = arena[pc+RPB]->GetBParamValue();

    switch (m_modifier)
    {
        case A:
        [[fallthrough]];
        case BA:
            if (IRB_ANUM == 0)
            {
                pc = RPA;
            }
            else 
            {
                pc = (pc+1) % ARENA_SIZE;
            }
            break;
        case B:
        [[fallthrough]];
        case AB:
            if (IRB_BNUM == 0)
            {
                pc = RPA;
            }
            else 
            {
                pc = (pc+1) % ARENA_SIZE;
            }
            break;
        case F:
        case X:
        case I:
            if ((IRB_ANUM == 0) && (IRB_BNUM == 0))
            {
                pc = RPA;
            }
            else 
            {
                pc = (pc+1) % ARENA_SIZE;
            }
            break;
        default:
            LOG_ERR("Undefined modifier has been set {}", ModifierToString(m_modifier));
            return false;
    }
    return true;
}
