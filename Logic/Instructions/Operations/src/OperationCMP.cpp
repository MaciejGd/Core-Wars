#include "OperationCMP.h"
#include "logger.h"
#include "Arena.h"
#include "Instruction.h"

COperationCMP::COperationCMP()
{
    m_name = "CMP";
}

std::unique_ptr<COperation> COperationCMP::clone() const
{
    return std::unique_ptr<COperation>(new COperationCMP{*this});
}

InstructionResult COperationCMP::Execute(int a_pointer, int b_pointer, int &pc)
{
    LOG_DBG("Executing {}.{} in memory cell {}", m_name, ModifierToString(m_modifier), pc);
    CArena& arena = CArena::GetInstance();

    // get reference to instructions pointed to by A and B params 
    auto& a_instr = arena[pc + a_pointer];
    auto& b_instr = arena[pc + b_pointer];

    switch (m_modifier)
    {
        case A:
            if (a_instr->GetAParamValue() == b_instr->GetAParamValue())
            {
                pc = (pc + 2) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc + 1) % ARENA_SIZE;
            }
            break;
        case B:
            if (a_instr->GetBParamValue() == b_instr->GetBParamValue())
            {
                pc = (pc + 2) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc + 1) % ARENA_SIZE;
            }
            break;
        case AB:
            if (a_instr->GetAParamValue() == b_instr->GetBParamValue())
            {
                pc = (pc + 2) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc + 1) % ARENA_SIZE;
            }
            break;
        case BA:
            if (a_instr->GetBParamValue() == b_instr->GetAParamValue())
            {
                pc = (pc + 2) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc + 1) % ARENA_SIZE;
            }
            break;
        case F:
            if (a_instr->GetAParamValue() == b_instr->GetAParamValue() &&
                a_instr->GetBParamValue() == b_instr->GetBParamValue())
            {
                pc = (pc + 2) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc + 1) % ARENA_SIZE;
            }
            break;
        case X:
            if (a_instr->GetAParamValue() == b_instr->GetBParamValue() &&
                a_instr->GetBParamValue() == b_instr->GetAParamValue())
            {
                pc = (pc + 2) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc + 1) % ARENA_SIZE;
            }
            break;
        case I:
            // compare whole instructions
            if (a_instr->PrintInstruction() == b_instr->PrintInstruction())
            {
                pc = (pc + 2) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc + 1) % ARENA_SIZE;
            }
            break;
        default:
            LOG_ERR("Undefined parameter in {}", m_name);
            return InstructionResult::FAIL;
    }
    return InstructionResult::PASS;
}
