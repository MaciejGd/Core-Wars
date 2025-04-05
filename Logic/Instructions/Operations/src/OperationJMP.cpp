#include "OperationJMP.h"
#include "Arena.h"

COperationJMP::COperationJMP()
{
    m_name = "JMP";
}

std::unique_ptr<COperation> COperationJMP::clone() const
{
    return std::unique_ptr<COperation>(new COperationJMP{*this});
}

InstructionResult COperationJMP::Execute(int a_pointer, int b_pointer, int &pc)
{
    pc += (a_pointer % ARENA_SIZE); // jump to address requested by read pointer of A
    return InstructionResult::PASS;
}
