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

    int b_pointer = B_param->GetPointer();
    int a_pointer = A_param->GetPointer();

    // A number of instruction pointed by A
    int IRA_ANUM = arena[pc+a_pointer]->GetAParamValue();
    // B number of instruction pointed by A 
    int IRA_BNUM = arena[pc+a_pointer]->GetBParamValue();

    auto& curr_instruction = arena[pc + b_pointer]; // to replace

    switch (m_modifier)
    {
        case ModifierType::A:
            // replace A param of instruction with A param of current instruction
            arena[pc + b_pointer]->SetAParamValue(IRA_ANUM);
            break;
        case ModifierType::B:
            // replace B param of instruction with B param of current instruction
            arena[pc + b_pointer]->SetBParamValue(IRA_BNUM);
            break;
        case ModifierType::AB:
            // replace B param of instruction with A param of current instruction
            arena[pc + b_pointer]->SetBParamValue(IRA_ANUM);
            break;
        case ModifierType::BA:
            // replace A param of instruction with B param of current instruction
            arena[pc + b_pointer]->SetAParamValue(IRA_BNUM);
            break;
        case ModifierType::F:
            // replace both As and Bs of instructions
            arena[pc + b_pointer]->SetAParamValue(IRA_ANUM);
            arena[pc + b_pointer]->SetBParamValue(IRA_BNUM);
            break;
        case ModifierType::X:
            // replace A with B and B with A
            arena[pc + b_pointer]->SetBParamValue(IRA_ANUM);
            arena[pc + b_pointer]->SetAParamValue(IRA_BNUM);
            break;
        case ModifierType::I:
        {
            // replace whole instruction at B pointed by A
            arena[pc + b_pointer].reset(new CInstruction{*arena[pc + a_pointer]});
            break;
        }
        default:
            LOG_ERR("Undefined parameter in {}", m_name);
            return false;
            break;
    }
    // PC should be increased by one after the operation succeed
    pc = (pc+1) % ARENA_SIZE;
    return true;
}
