#include "OperationEND.h"

COperationEND::COperationEND()
{
    m_name = "END";
}

std::unique_ptr<COperation> COperationEND::clone() const
{
    return std::unique_ptr<COperation>(new COperationEND{*this});
}

InstructionResult COperationEND::Execute(int a_pointer, int b_pointer, int &pc)
{
    return InstructionResult::FAIL;
}
