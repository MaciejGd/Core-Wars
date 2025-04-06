#include "OperationJMP.h"
#include "Arena.h"
#include "DefaultModSetterJump.h"
#include "logger.h"

COperationJMP::COperationJMP()
{
    m_name = "JMP";
    m_def_modifier = std::make_unique<CDefaultModSetterJump>();
}

std::unique_ptr<COperation> COperationJMP::clone() const
{
    return std::unique_ptr<COperation>(new COperationJMP{*this});
}

InstructionResult COperationJMP::Execute(int a_pointer, int b_pointer, int &pc)
{
    pc = (pc + a_pointer) % ARENA_SIZE; // jump to address requested by read pointer of A
    LOG_ERR("Jumping to pointer {}", a_pointer);
    return InstructionResult::PASS;
}
