#include "OperationJMP.h"
#include "Parameter.h"
#include "Arena.h"

COperationJMP::COperationJMP()
{
    m_name = "JMP";
}

std::unique_ptr<COperation> COperationJMP::clone() const
{
    return std::unique_ptr<COperation>(new COperationJMP{*this});
}

InstructionResult COperationJMP::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    int a_pointer = A_param->GetPointer();
    pc += (a_pointer % ARENA_SIZE); // jump to address requested by read pointer of A
    return InstructionResult::PASS;
}
