#include "OperationSPL.h"

COperationSPL::COperationSPL()
{
    m_name = "SPL";
}

std::unique_ptr<COperation> COperationSPL::clone() const
{
    return std::unique_ptr<COperation>(new COperationSPL{*this});
}

InstructionResult COperationSPL::Execute(int a_pointer, int b_pointer, int &pc)
{
    // TODO
    // I should add special handling of SPL operation
    pc = pc + a_pointer;
    return InstructionResult::SPLIT;
}
