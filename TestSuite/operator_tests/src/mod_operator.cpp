#include "mod_operator.h"
#include "OperationMOD.h"
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

void MODOperatorTest::RunTests()
{
    m_testA();
    m_testB();
    m_testAB();
    m_testBA();
    m_testX();
    m_testF();
    m_testI();
}

void MODOperatorTest::m_testA()
{
    CArena& arena = m_testInit(ModifierType::A);
    // set both A and B to one 
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(4);
    arena[STARTING_ADDRESS+B_VAL]->SetBParamValue(1);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(3);
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

void MODOperatorTest::m_testB()
{
    CArena& arena = m_testInit(ModifierType::B);
    // set both A and B to one 
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS+B_VAL]->SetBParamValue(4);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(3);
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

void MODOperatorTest::m_testAB()
{
    CArena& arena = m_testInit(ModifierType::AB);
    // set both A and B to one 
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(10);
    arena[STARTING_ADDRESS+B_VAL]->SetBParamValue(1);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(8);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly moved on cell further");
    }
    else 
    {
        LOG_FAIL("Moved {} cells", nSTARTING_ADDRESS - STARTING_ADDRESS);
    }

    if (arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == 2)
    {
        LOG_PASS("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }   
    else {
        LOG_FAIL("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
}

void MODOperatorTest::m_testBA()
{
    CArena& arena = m_testInit(ModifierType::BA);
    // set both A and B to one 
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS+B_VAL]->SetBParamValue(10);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(8);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly moved on cell further");
    }
    else 
    {
        LOG_FAIL("Moved {} cells", nSTARTING_ADDRESS - STARTING_ADDRESS);
    }

    if (arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == 2)
    {
        LOG_PASS("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }   
    else {
        LOG_FAIL("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
}

void MODOperatorTest::m_testX()
{
    CArena& arena = m_testInit(ModifierType::X);
    // set both A and B to one 
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(12);
    arena[STARTING_ADDRESS+B_VAL]->SetBParamValue(6);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(5);
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(5);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly moved on cell further");
    }
    else 
    {
        LOG_FAIL("Moved {} cells", nSTARTING_ADDRESS - STARTING_ADDRESS);
    }

    if (arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == 2 &&
        arena[STARTING_ADDRESS + B_VAL]->GetAParamValue() == 1)
    {
        LOG_PASS("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }   
    else {
        LOG_FAIL("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
}

void MODOperatorTest::m_testF()
{
    m_testIF(ModifierType::F);
}

void MODOperatorTest::m_testI()
{
    m_testIF(ModifierType::I);
}

void MODOperatorTest::m_testIF(ModifierType mod)
{
    CArena& arena = m_testInit(mod);
    // set both A and B to one 
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(12);
    arena[STARTING_ADDRESS+B_VAL]->SetBParamValue(6);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(5);
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(5);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly moved on cell further");
    }
    else 
    {
        LOG_FAIL("Moved {} cells", nSTARTING_ADDRESS - STARTING_ADDRESS);
    }

    if (arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == 2 &&
        arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == 1)
    {
        LOG_PASS("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }   
    else {
        LOG_FAIL("Instruction at STARTING_ADDRESS+B_VAL after sub operation: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(0);
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    if (!arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS))
    {
        LOG_PASS("Properly failed to execute as division by zero occured");
    }
    else {
        LOG_FAIL("Execution succeed even though division by zero occured");
    }

}

CArena& MODOperatorTest::m_testInit(ModifierType mod)
{
    LOG_WRN("Testing modifier {}", ModifierToString(mod));
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    arena[STARTING_ADDRESS] = std::move(MODOperatorTest::CreateMODPtr(A_VAL, B_VAL, mod));
    return arena;
}  

std::unique_ptr<CInstruction> MODOperatorTest::CreateMODPtr(int a, int b, ModifierType mod)
{
    // create params with immediate addressing
    std::unique_ptr<CParameter> A_param(new CParameterDirect());
    std::unique_ptr<CParameter> B_param(new CParameterDirect());
    A_param->SetValue(a);
    B_param->SetValue(b);
    // create mov operation with modifier
    std::unique_ptr<COperation> op(new COperationMOD());
    op->SetModifier(mod);
    // create mov instruction
    std::unique_ptr<CInstruction> ret(new CInstruction());
    ret->SetOperation(std::move(op));
    ret->SetAParameter(std::move(A_param));
    ret->SetBParameter(std::move(B_param));
    return ret;
}