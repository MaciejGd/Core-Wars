#include "add_operator.h"
#include "OperationADD.h"
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

void ADDOperatorTest::RunTests()
{
    m_testA();
    m_testB();
    m_testAB();
    m_testBA();
    m_testX();
    m_testF();
    m_testI();
}

void ADDOperatorTest::m_testA()
{
    CArena& arena = m_testInit(ModifierType::A);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly moved on cell further");
    }
    else 
    {
        LOG_FAIL("Moved {} cells", nSTARTING_ADDRESS - STARTING_ADDRESS);
    }

    if (arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == 1)
    {
        LOG_PASS("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }   
    else {
        LOG_FAIL("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
}

void ADDOperatorTest::m_testB()
{
    CArena& arena = m_testInit(ModifierType::B);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(1);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly moved on cell further");
    }
    else 
    {
        LOG_FAIL("Moved {} cells", nSTARTING_ADDRESS - STARTING_ADDRESS);
    }

    if (arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == 1)
    {
        LOG_PASS("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }   
    else {
        LOG_FAIL("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
}

void ADDOperatorTest::m_testAB()
{
    CArena& arena = m_testInit(ModifierType::AB);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(1);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly moved on cell further");
    }
    else 
    {
        LOG_FAIL("Moved {} cells", nSTARTING_ADDRESS - STARTING_ADDRESS);
    }

    if (arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == 1)
    {
        LOG_PASS("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }   
    else {
        LOG_FAIL("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
}

void ADDOperatorTest::m_testBA()
{
    CArena& arena = m_testInit(ModifierType::BA);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly moved on cell further");
    }
    else 
    {
        LOG_FAIL("Moved {} cells", nSTARTING_ADDRESS - STARTING_ADDRESS);
    }

    if (arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == 1)
    {
        LOG_PASS("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }   
    else {
        LOG_FAIL("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
}

void ADDOperatorTest::m_testX()
{
    CArena& arena = m_testInit(ModifierType::X);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(2);
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(1);
    LOG_PASS("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly moved on cell further");
    }
    else 
    {
        LOG_FAIL("Moved {} cells", nSTARTING_ADDRESS - STARTING_ADDRESS);
    }

    if (arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == 1 &&
        arena[STARTING_ADDRESS + B_VAL]->GetAParamValue() == 2)
    {
        LOG_PASS("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }   
    else {
        LOG_FAIL("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
}

void ADDOperatorTest::m_testF()
{
    m_testIF(ModifierType::F);
}

void ADDOperatorTest::m_testI()
{
    m_testIF(ModifierType::I);
}

void ADDOperatorTest::m_testIF(ModifierType mod)
{
    CArena& arena = m_testInit(mod);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(2);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly moved on cell further");
    }
    else 
    {
        LOG_FAIL("Moved {} cells", nSTARTING_ADDRESS - STARTING_ADDRESS);
    }

    if (arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == 1 &&
        arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == 2)
    {
        LOG_PASS("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }   
    else {
        LOG_FAIL("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
}

CArena& ADDOperatorTest::m_testInit(ModifierType mod)
{
    LOG_WRN("Testing modifier {}", ModifierToString(mod));
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    arena[STARTING_ADDRESS] = std::move(ADDOperatorTest::CreateADDPtr(A_VAL, B_VAL, mod));
    return arena;
}  

std::unique_ptr<CInstruction> ADDOperatorTest::CreateADDPtr(int a, int b, ModifierType mod)
{
    // create params with immediate addressing
    std::unique_ptr<CParameter> A_param(new CParameterDirect());
    std::unique_ptr<CParameter> B_param(new CParameterDirect());
    A_param->SetValue(a);
    B_param->SetValue(b);
    // create mov operation with modifier
    std::unique_ptr<COperation> op(new COperationADD());
    op->SetModifier(mod);
    // create mov instruction
    std::unique_ptr<CInstruction> ret(new CInstruction());
    ret->SetOperation(std::move(op));
    ret->SetAParameter(std::move(A_param));
    ret->SetBParameter(std::move(B_param));
    return ret;
}