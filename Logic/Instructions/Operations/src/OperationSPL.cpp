#include "OperationSPL.h"
#include "Parameter.h"

COperationSPL::COperationSPL()
{
    m_name = "SPL";
}

std::unique_ptr<COperation> COperationSPL::clone() const
{
    return std::unique_ptr<COperation>(new COperationSPL{*this});
}

InstructionResult COperationSPL::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    // TODO
    // I should add special handling of SPL operation
    int PA = A_param->GetPointer();
    pc = pc + PA;
    return InstructionResult::SPLIT;
}
