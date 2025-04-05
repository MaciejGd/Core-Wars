#include "OperationEQU.h"

COperationEQU::COperationEQU()
{
    m_name = "EQU";
}

std::unique_ptr<COperation> COperationEQU::clone() const
{
    return std::unique_ptr<COperation>(new COperationEQU{*this});
}

InstructionResult COperationEQU::Execute(int a_pointer, int b_pointer, int &pc)
{
    return InstructionResult::FAIL;
}
