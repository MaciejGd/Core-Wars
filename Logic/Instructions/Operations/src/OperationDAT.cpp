#include "OperationDAT.h"

COperationDAT::COperationDAT()
{
    m_name = "DAT";
}

std::unique_ptr<COperation> COperationDAT::clone() const
{
    return std::unique_ptr<COperation>(new COperationDAT{*this});
}

InstructionResult COperationDAT::Execute(int a_pointer, int b_pointer, int &pc)
{
    // executing DAT operation will lead to immediate fail
    return InstructionResult::FAIL;
}
