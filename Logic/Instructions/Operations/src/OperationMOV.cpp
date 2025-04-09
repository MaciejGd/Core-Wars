#include "OperationMOV.h"
#include "Arena.h"
#include "Instruction.h"
#include "logger.h"
#include "DefaultModSetterMOV.h"

COperationMOV::COperationMOV()
{
    m_name = "MOV";
    m_def_modifier = std::make_unique<CDefaultModSetterMOV>();
}

std::unique_ptr<COperation> COperationMOV::clone() const
{
    return std::unique_ptr<COperation>(new COperationMOV{*this});
}

InstructionResult COperationMOV::Execute(int a_pointer, int b_pointer, int &pc, int &modified_cell)
{
    LOG_DBG("Executing {}.{} in memory cell {}", m_name, ModifierToString(m_modifier), pc);
    CArena& arena = CArena::GetInstance();

    

    // A number of instruction pointed by A
    int IRA_ANUM = arena[pc+a_pointer]->GetAParamValue();
    // B number of instruction pointed by A 
    int IRA_BNUM = arena[pc+a_pointer]->GetBParamValue();

    auto& IRB = arena[pc + b_pointer]; // to replace

    switch (m_modifier)
    {
        case ModifierType::A:
            // replace A param of instruction with A param of current instruction
            IRB->SetAParamValue(IRA_ANUM);
            break;
        case ModifierType::B:
            // replace B param of instruction with B param of current instruction
            IRB->SetBParamValue(IRA_BNUM);
            break;
        case ModifierType::AB:
            // replace B param of instruction with A param of current instruction
            IRB->SetBParamValue(IRA_ANUM);
            break;
        case ModifierType::BA:
            // replace A param of instruction with B param of current instruction
            IRB->SetAParamValue(IRA_BNUM);
            break;
        case ModifierType::F:
            // replace both As and Bs of instructions
            IRB->SetAParamValue(IRA_ANUM);
            IRB->SetBParamValue(IRA_BNUM);
            break;
        case ModifierType::X:
            // replace A with B and B with A
            IRB->SetBParamValue(IRA_ANUM);
            IRB->SetAParamValue(IRA_BNUM);
            break;
        case ModifierType::I:
        {
            // replace whole instruction at B pointed by A
            IRB.reset(new CInstruction{*arena[pc + a_pointer]});
            break;
        }
        default:
            LOG_ERR("Undefined parameter in {}", m_name);
            return InstructionResult::FAIL;
            break;
    }
    // update modified cell as it was modified
    modified_cell = (pc + b_pointer) % ARENA_SIZE;
    // PC should be increased by one after the operation succeed
    pc = (pc+1) % ARENA_SIZE;
    return InstructionResult::PASS;
}
