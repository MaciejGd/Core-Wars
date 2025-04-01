#include "jmn_operator.h"
#include "OperationJMN.h"
#include "Parameter.h"
#include "Arena.h"
#include "Instruction.h"
#include "logger.h"
#include "ParameterImmediate.h"
#include "ParameterDirect.h"
#include "ParameterIndirect.h"

#define STARTING_ADDRESS 100
#define A_VAL 10
#define B_VAL 20

void JMNOperatorTest::RunTests()
{
    m_testA();
    m_testBA();
    m_testB();
    m_testAB();
    m_testX();
    m_testI();
    m_testF();
}

void JMNOperatorTest::m_testA()
{
    LOG_WRN("Testing A modfifier");
    m_Atests(ModifierType::A);
}

void JMNOperatorTest::m_testBA()
{
    LOG_WRN("Testing BA modfifier");
    m_Atests(ModifierType::BA);
}

void JMNOperatorTest::m_testB()
{
    LOG_WRN("Testing B modfifier");
    m_Btests(ModifierType::B);
}

void JMNOperatorTest::m_testAB()
{
    LOG_WRN("Testing AB modfifier");
    m_Btests(ModifierType::AB);
}

void JMNOperatorTest::m_testX()
{
    LOG_WRN("Testing X modfifier");
    m_DoubleParamCheck(ModifierType::X);
}

void JMNOperatorTest::m_testI()
{
    LOG_WRN("Testing I modfifier");
    m_DoubleParamCheck(ModifierType::I);
}

void JMNOperatorTest::m_testF()
{
    LOG_WRN("Testing F modfifier");
    m_DoubleParamCheck(ModifierType::F);
}

void JMNOperatorTest::m_Atests(ModifierType mod)
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();

    // fill arena field and execute instruction
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = JMNOperatorTest::CreateJMNPtr(A_VAL, B_VAL, mod);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    LOG_WRN("A pointer value: {}", arena[STARTING_ADDRESS]->GetAParam()->GetPointer());
    if (nSTARTING_ADDRESS == STARTING_ADDRESS+1)
    {
        LOG_PASS("Properly jumped to {}", nSTARTING_ADDRESS);
    }
    else 
    {
        LOG_FAIL("Failed current address {}", nSTARTING_ADDRESS);
    }
    // setting param value to 10
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS + B_VAL]->SetAParamValue(10);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + A_VAL)
    {
        LOG_PASS("Properly jumped to {}", nSTARTING_ADDRESS);
    }
    else 
    {
        LOG_FAIL("Failed current address {}", nSTARTING_ADDRESS);
    }
}

void JMNOperatorTest::m_Btests(ModifierType mod)
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    // fill arena field and execute instruction
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = JMNOperatorTest::CreateJMNPtr(A_VAL, B_VAL, mod);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);

    if (nSTARTING_ADDRESS == STARTING_ADDRESS+1)
    {
        LOG_PASS("Current address: {}", nSTARTING_ADDRESS);
    }
    else 
    {
        LOG_FAIL("Failed current address {}", nSTARTING_ADDRESS);
    }
    // setting param value to 10
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS + B_VAL]->SetBParamValue(10);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + A_VAL)
    {
        LOG_PASS("Address after jump: {}", nSTARTING_ADDRESS);
    }
    else 
    {
        LOG_FAIL("Failed to jump to {}", nSTARTING_ADDRESS);
    }
}

void JMNOperatorTest::m_DoubleParamCheck(ModifierType mod)
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();

    // fill arena field and execute instruction
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = JMNOperatorTest::CreateJMNPtr(A_VAL, B_VAL, mod);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);

    if (nSTARTING_ADDRESS == STARTING_ADDRESS+1)
    {
        LOG_PASS("Properly jumped to {}", nSTARTING_ADDRESS);
    }
    else 
    {
        LOG_FAIL("Failed current address {}", nSTARTING_ADDRESS);
    }
    // setting param value to 10
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS + B_VAL]->SetBParamValue(10);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + A_VAL)
    {
        LOG_PASS("Properly jumped to {}", nSTARTING_ADDRESS);
    }
    else 
    {
        LOG_FAIL("Failed current address {}", nSTARTING_ADDRESS);
    }
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS + B_VAL]->SetBParamValue(0);
    arena[STARTING_ADDRESS + B_VAL]->SetAParamValue(10);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + A_VAL)
    {
        LOG_PASS("Properly jumped to {}", nSTARTING_ADDRESS);
    }
    else 
    {
        LOG_FAIL("Failed current address {}", nSTARTING_ADDRESS);
    }
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS + B_VAL]->SetBParamValue(10);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + A_VAL)
    {
        LOG_PASS("Properly jumped to {}", nSTARTING_ADDRESS);
    }
    else 
    {
        LOG_FAIL("Failed current address {}", nSTARTING_ADDRESS);
    }
}

std::unique_ptr<CInstruction> JMNOperatorTest::CreateJMNPtr(int a, int b, ModifierType mod)
{
    // create params with immediate addressing
    std::unique_ptr<CParameter> A_param(new CParameterDirect());
    std::unique_ptr<CParameter> B_param(new CParameterDirect());
    A_param->SetValue(a);
    B_param->SetValue(b);
    // create mov operation with modifier
    std::unique_ptr<COperation> op(new COperationJMN());
    op->SetModifier(mod);
    // create mov instruction
    std::unique_ptr<CInstruction> ret(new CInstruction());
    ret->SetOperation(std::move(op));
    ret->SetAParameter(std::move(A_param));
    ret->SetBParameter(std::move(B_param));
    return ret;
}

