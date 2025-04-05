#include "OperationEQU.h"

COperationEQU::COperationEQU()
{
    m_name = "EQU";
}

std::unique_ptr<COperation> COperationEQU::clone() const
{
    return std::unique_ptr<COperation>(new COperationEQU{*this});
}

InstructionResult COperationEQU::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return InstructionResult::FAIL;
}
