#include "djn_operator.h"
#include "OperationDJN.h"
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


void DJNOperatorTest::RunTests()
{
    m_testA();
    m_testBA();
    m_testB();
    m_testAB();
    m_testX();
    m_testI();
    m_testF();
}


void DJNOperatorTest::m_testA()
{
    LOG_WRN("Testing A modfifier");
    m_Atests(ModifierType::A);
}

void DJNOperatorTest::m_testBA()
{
    LOG_WRN("Testing BA modfifier");
    m_Atests(ModifierType::BA);
}

void DJNOperatorTest::m_testB()
{
    LOG_WRN("Testing B modfifier");
    m_Btests(ModifierType::B);
}

void DJNOperatorTest::m_testAB()
{
    LOG_WRN("Testing AB modfifier");
    m_Btests(ModifierType::AB);
}

void DJNOperatorTest::m_testX()
{
    LOG_WRN("Testing X modfifier");
    m_DoubleParamCheck(ModifierType::X);
}

void DJNOperatorTest::m_testI()
{
    LOG_WRN("Testing I modfifier");
    m_DoubleParamCheck(ModifierType::I);
}

void DJNOperatorTest::m_testF()
{
    LOG_WRN("Testing F modfifier");
    m_DoubleParamCheck(ModifierType::F);
}

void DJNOperatorTest::m_Atests(ModifierType mod)
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();

    // fill arena field and execute instruction
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = DJNOperatorTest::CreateDJNPtr(A_VAL, B_VAL, mod);
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS, modified_cell);
    LOG_WRN("A pointer value: {}", arena[STARTING_ADDRESS]->GetAParam()->GetPointer());
    if (nSTARTING_ADDRESS == STARTING_ADDRESS+1 &&
            arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == 0)
    {
        LOG_PASS("Properly jumped to {}, changed arena field: {}", nSTARTING_ADDRESS,
            arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Failed current address {}", nSTARTING_ADDRESS);
    }
    // setting param value to 10
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS, modified_cell);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + A_VAL)
    {
        LOG_PASS("Properly jumped to {}", nSTARTING_ADDRESS);
    }
    else 
    {
        LOG_FAIL("Failed current address {}", nSTARTING_ADDRESS);
    }
}

void DJNOperatorTest::m_Btests(ModifierType mod)
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    // fill arena field and execute instruction
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = DJNOperatorTest::CreateDJNPtr(A_VAL, B_VAL, mod);
    arena[STARTING_ADDRESS + B_VAL]->SetBParamValue(1); // we need to make sure it will be equal to zero after operation execution
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS, modified_cell);
    
    if (nSTARTING_ADDRESS == STARTING_ADDRESS+1 &&
        arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == 0)
    {
        LOG_PASS("Properly jumped to {}, changed arena field: {}", nSTARTING_ADDRESS,
            arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Failed current address {}", nSTARTING_ADDRESS);
    }
    // setting param value to 10
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS + B_VAL]->SetBParamValue(10);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS, modified_cell);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + A_VAL)
    {
        LOG_PASS("Address after jump: {}", nSTARTING_ADDRESS);
    }
    else 
    {
        LOG_FAIL("Failed to jump to {}", nSTARTING_ADDRESS);
    }
}

void DJNOperatorTest::m_DoubleParamCheck(ModifierType mod)
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();

    // fill arena field and execute instruction
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = DJNOperatorTest::CreateDJNPtr(A_VAL, B_VAL, mod);
    arena[STARTING_ADDRESS + B_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS + B_VAL]->SetBParamValue(1);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS, modified_cell);

    if (nSTARTING_ADDRESS == STARTING_ADDRESS+1 &&
        arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == 0 &&
        arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == 0)
    {
        LOG_PASS("Properly jumped to {}, changed arena field: {}", nSTARTING_ADDRESS,
            arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Failed current address {}", nSTARTING_ADDRESS);
    }
    // setting param value to 10
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS + B_VAL]->SetBParamValue(10);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS, modified_cell);
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
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS, modified_cell);
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
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS, modified_cell);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + A_VAL)
    {
        LOG_PASS("Properly jumped to {}", nSTARTING_ADDRESS);
    }
    else 
    {
        LOG_FAIL("Failed current address {}", nSTARTING_ADDRESS);
    }
}


std::unique_ptr<CInstruction> DJNOperatorTest::CreateDJNPtr(int a, int b, ModifierType mod)
{
    // create params with immediate addressing
    std::unique_ptr<CParameter> A_param(new CParameterDirect());
    std::unique_ptr<CParameter> B_param(new CParameterDirect());
    A_param->SetValue(a);
    B_param->SetValue(b);
    // create mov operation with modifier
    std::unique_ptr<COperation> op(new COperationDJN());
    op->SetModifier(mod);
    // create mov instruction
    std::unique_ptr<CInstruction> ret(new CInstruction());
    ret->SetOperation(std::move(op));
    ret->SetAParameter(std::move(A_param));
    ret->SetBParameter(std::move(B_param));
    return ret;
}
