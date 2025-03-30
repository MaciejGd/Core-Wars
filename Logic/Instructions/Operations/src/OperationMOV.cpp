#include "OperationMOV.h"
#include "Arena.h"
#include "Parameter.h"
#include "Instruction.h"
#include "logger.h"

COperationMOV::COperationMOV()
{
    m_name = "MOV";
}

std::unique_ptr<COperation> COperationMOV::clone() const
{
    return std::unique_ptr<COperation>(new COperationMOV{*this});
}

bool COperationMOV::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    LOG_DBG("Executing {}.{} in memory cell {}", m_name, ModifierToString(m_modifier), pc);
    CArena& arena = CArena::GetInstance();
    int WPB = B_param->GetWritePointer();
    switch (m_modifier)
    {
        case ModifierType::A:
            // replace A param of instruction with A param of current instruction
            arena[pc + WPB]->SetAParamValue(A_param->GetValue());
            break;
        case ModifierType::B:
            // replace B param of instruction with B param of current instruction
            arena[pc + WPB]->SetBParamValue(B_param->GetValue());
            break;
        case ModifierType::AB:
            // replace B param of instruction with A param of current instruction
            arena[pc + WPB]->SetBParamValue(A_param->GetValue());
            break;
        case ModifierType::BA:
            // replace A param of instruction with B param of current instruction
            arena[pc + WPB]->SetAParamValue(B_param->GetValue());
            break;
        case ModifierType::F:
            // replace both As and Bs of instructions
            arena[pc + WPB]->SetAParamValue(A_param->GetValue());
            arena[pc + WPB]->SetBParamValue(B_param->GetValue());
            break;
        case ModifierType::X:
            // replace A with B and B with A
            arena[pc + WPB]->SetBParamValue(A_param->GetValue());
            arena[pc + WPB]->SetAParamValue(B_param->GetValue());
            break;
        case ModifierType::I:
        {
            // replace whole instruction at B pointed by A
            int RPA = A_param->GetReadPointer();
            arena[pc + WPB].reset(new CInstruction{*arena[pc + RPA]});
            break;
        }
        default:
            LOG_ERR("Undefined parameter in {}", m_name);
            return false;
            break;
    }
    return true;
}
