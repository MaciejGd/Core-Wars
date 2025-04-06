#include "OperationJMN.h"
#include "Arena.h"
#include "Instruction.h" 
#include "logger.h"
#include "DefaultModSetterJump.h"

COperationJMN::COperationJMN()
{
    m_name = "JMN";
    m_def_modifier = std::make_unique<CDefaultModSetterJump>();
}

std::unique_ptr<COperation> COperationJMN::clone() const
{
    return std::unique_ptr<COperation>(new COperationJMN{*this});
}

InstructionResult COperationJMN::Execute(int a_pointer, int b_pointer, int &pc)
{
    LOG_DBG("Executing {}.{} in memory cell {}", m_name, ModifierToString(m_modifier), pc);
    CArena& arena = CArena::GetInstance(); // TODO turn it into a macro

    
    // A number of instruction pointed by B param
    int IRB_ANUM = arena[pc+b_pointer]->GetAParamValue();
    // B number of instruction pointed by B param
    int IRB_BNUM = arena[pc+b_pointer]->GetBParamValue();

    switch (m_modifier)
    {
        case A:
        [[fallthrough]];
        case BA:
            if (IRB_ANUM != 0)
            {
                pc = (pc + a_pointer) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc+1) % ARENA_SIZE;
            }
            break;
        case B:
        [[fallthrough]];
        case AB:
            if (IRB_BNUM != 0)
            {
                pc = (pc + a_pointer) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc+1) % ARENA_SIZE;
            }
            break;
        case F:
        case X:
        case I:
            if ((IRB_ANUM != 0) || (IRB_BNUM != 0))
            {
                pc = (pc + a_pointer) % ARENA_SIZE;
            }
            else 
            {
                pc = (pc+1) % ARENA_SIZE;
            }
            break;
        default:
            LOG_ERR("Undefined modifier has been set {}", ModifierToString(m_modifier));
            return InstructionResult::FAIL;
    }
    return InstructionResult::PASS;
}
