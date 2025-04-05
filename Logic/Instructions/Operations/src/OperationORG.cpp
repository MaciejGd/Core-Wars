#include "OperationORG.h"

COperationORG::COperationORG()
{
    m_name = "ORG";
}

std::unique_ptr<COperation> COperationORG::clone() const
{
    return std::unique_ptr<COperation>(new COperationORG{*this});
}

InstructionResult COperationORG::Execute(int a_pointer, int b_pointer, int &pc)
{
    return InstructionResult::FAIL;
}
