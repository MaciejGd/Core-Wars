#include "jmp_operator.h"
#include "OperationJMP.h"
#include "Parameter.h"
#include "Arena.h"
#include "Instruction.h"
#include "logger.h"
#include "ParameterImmediate.h"
#include "ParameterDirect.h"
#include "ParameterIndirect.h"

#define STARTING_POINT 100
#define A_VAL 10
#define B_VAL 20


void JMPOperatorTest::RunTests()
{
    m_testA();
}


void JMPOperatorTest::m_testA()
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    arena[STARTING_POINT] = JMPOperatorTest::CreateJMPPtr(A_VAL, B_VAL, ModifierType::A);
    
    int nSTARTING_POINT = STARTING_POINT;
    arena[STARTING_POINT]->Execute(nSTARTING_POINT, modified_cell);

    if (nSTARTING_POINT == STARTING_POINT + A_VAL)
    {
        LOG_PASS("Properly jumped to A val, current PC: {}", nSTARTING_POINT);
    }
    else 
    {
        LOG_FAIL("Failed jumping to A val, current PC: {}", nSTARTING_POINT);
    }
}

std::unique_ptr<CInstruction> JMPOperatorTest::CreateJMPPtr(int a, int b, ModifierType mod)
{
    // create params with immediate addressing
    std::unique_ptr<CParameter> A_param(new CParameterDirect());
    std::unique_ptr<CParameter> B_param(new CParameterDirect());
    A_param->SetValue(a);
    B_param->SetValue(b);
    // create mov operation with modifier
    std::unique_ptr<COperation> op(new COperationJMP());
    op->SetModifier(mod);
    // create mov instruction
    std::unique_ptr<CInstruction> ret(new CInstruction());
    ret->SetOperation(std::move(op));
    ret->SetAParameter(std::move(A_param));
    ret->SetBParameter(std::move(B_param));
    return ret;
}


