#include "OperationEQU.h"
#include "DefaultModSetterJump.h"

COperationEQU::COperationEQU()
{
    m_name = "EQU";
    // to be removed
    m_def_modifier = std::make_unique<CDefaultModSetterJump>();
}

std::unique_ptr<COperation> COperationEQU::clone() const
{
    return std::unique_ptr<COperation>(new COperationEQU{*this});
}

InstructionResult COperationEQU::Execute(int a_pointer, int b_pointer, int &pc)
{
    return InstructionResult::FAIL;
}
