#include "OperationSPL.h"
#include "Arena.h"
#include "DefaultModSetterJump.h"

COperationSPL::COperationSPL()
{
    m_name = "SPL";
    m_def_modifier = std::make_unique<CDefaultModSetterJump>();
}

std::unique_ptr<COperation> COperationSPL::clone() const
{
    return std::unique_ptr<COperation>(new COperationSPL{*this});
}

InstructionResult COperationSPL::Execute(int a_pointer, int b_pointer, int &pc)
{
    // TODO
    // I should add special handling of SPL operation
    pc = (pc + a_pointer) % ARENA_SIZE;
    return InstructionResult::SPLIT;
}
