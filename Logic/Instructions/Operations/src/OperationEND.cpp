#include "OperationEND.h"
#include "DefaultModSetterJump.h"

COperationEND::COperationEND()
{
    m_name = "END";
    m_def_modifier = std::make_unique<CDefaultModSetterJump>();
}

std::unique_ptr<COperation> COperationEND::clone() const
{
    return std::unique_ptr<COperation>(new COperationEND{*this});
}

InstructionResult COperationEND::Execute(int a_pointer, int b_pointer, int &pc)
{
    return InstructionResult::FAIL;
}
