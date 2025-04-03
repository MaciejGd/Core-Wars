#include "slt_operator.h"
#include "OperationSLT.h"
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

void SLTOperatorTest::RunTests()
{
    m_testA();
    m_testB();
    m_testBA();
    m_testAB();
    m_testX();
    m_testF();
    m_testI();
}

void SLTOperatorTest::m_testA()
{
    LOG_WRN("Running test for modifier: {}", ModifierToString(ModifierType::A));
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    arena[STARTING_ADDRESS] = SLTOperatorTest::CreateSLTPtr(A_VAL, B_VAL, ModifierType::A);
    // initially instruction at 110 and instr in 120 should have same A so jump+2
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 2)
    {
        LOG_PASS("Properly jumped 2 cells, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    // now change A param value of cell 110
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(0);
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly jumped 1 cell, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
}

void SLTOperatorTest::m_testB()
{
    LOG_WRN("Running test for modifier: {}", ModifierToString(ModifierType::B));
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    arena[STARTING_ADDRESS] = SLTOperatorTest::CreateSLTPtr(A_VAL, B_VAL, ModifierType::B);
    // initially instruction at 110 and instr in 120 should have same B so jump+2
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+B_VAL]->SetBParamValue(1);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 2)
    {
        LOG_PASS("Properly jumped 2 cells, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    // now change B param value of cell 110
    arena[STARTING_ADDRESS+B_VAL]->SetBParamValue(0);
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly jumped 1 cell, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
}

void SLTOperatorTest::m_testBA()
{
    LOG_WRN("Running test for modifier: {}", ModifierToString(ModifierType::BA));
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    arena[STARTING_ADDRESS] = SLTOperatorTest::CreateSLTPtr(A_VAL, B_VAL, ModifierType::BA);
    // initially both A of first and B of second should be equal to zero
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 2)
    {
        LOG_PASS("Properly jumped 2 cells, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    // now change B param value of cell 110
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(2);
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly jumped 1 cell, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
}

void SLTOperatorTest::m_testAB()
{
    LOG_WRN("Running test for modifier: {}", ModifierToString(ModifierType::AB));
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    arena[STARTING_ADDRESS] = SLTOperatorTest::CreateSLTPtr(A_VAL, B_VAL, ModifierType::AB);
    arena[STARTING_ADDRESS+B_VAL]->SetBParamValue(1);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 2)
    {
        LOG_PASS("Properly jumped 2 cells, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(1);
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly jumped 1 cell, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
}

void SLTOperatorTest::m_testX()
{
    LOG_WRN("Running test for modifier: {}", ModifierToString(ModifierType::X));
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    arena[STARTING_ADDRESS] = SLTOperatorTest::CreateSLTPtr(A_VAL, B_VAL, ModifierType::X);
    // initially instruction at 110 and instr in 120 should have same B so jump+2
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS+B_VAL]->SetBParamValue(1);
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 2)
    {
        LOG_PASS("Properly jumped 2 cells, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    // now change B param value of cell 110
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(1);
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly jumped 1 cell, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }

    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(1);
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly jumped 1 cell, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
}

void SLTOperatorTest::m_testF()
{
    LOG_WRN("Running test for modifier: {}", ModifierToString(ModifierType::F));
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    arena[STARTING_ADDRESS] = SLTOperatorTest::CreateSLTPtr(A_VAL, B_VAL, ModifierType::F);
    // initially instruction at 110 and instr in 120 should have same B so jump+2
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS+B_VAL]->SetBParamValue(1);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 2)
    {
        LOG_PASS("Properly jumped 2 cells, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    // now change B param value of cell 110
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(1);
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly jumped 1 cell, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(0);
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly jumped 1 cell, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
}

void SLTOperatorTest::m_testI()
{
    LOG_WRN("Running test for modifier: {}", ModifierToString(ModifierType::I));
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    arena[STARTING_ADDRESS] = SLTOperatorTest::CreateSLTPtr(A_VAL, B_VAL, ModifierType::F);
    // initially instruction at 110 and instr in 120 should have same B so jump+2
    int nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS+B_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS+B_VAL]->SetBParamValue(1);
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 2)
    {
        LOG_PASS("Properly jumped 2 cells, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    // now change B param value of cell 110
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(1);
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly jumped 1 cell, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    arena[STARTING_ADDRESS+A_VAL]->SetAParamValue(1);
    arena[STARTING_ADDRESS+A_VAL]->SetBParamValue(0);
    nSTARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS]->Execute(nSTARTING_ADDRESS);
    if (nSTARTING_ADDRESS == STARTING_ADDRESS + 1)
    {
        LOG_PASS("Properly jumped 1 cell, instruction at PC+A_VAL=110: {}, instruction at PC+B_VAL: {}", 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Jumped {} cells, instruction at PC+A_VAL: {}, instrcution at PC+B_VAL: {}", nSTARTING_ADDRESS - STARTING_ADDRESS, 
            arena[STARTING_ADDRESS + A_VAL]->PrintInstruction(), arena[STARTING_ADDRESS + B_VAL]->PrintInstruction());
    }
}


std::unique_ptr<CInstruction> SLTOperatorTest::CreateSLTPtr(int a, int b, ModifierType mod)
{
    // create params with immediate addressing
    std::unique_ptr<CParameter> A_param(new CParameterDirect());
    std::unique_ptr<CParameter> B_param(new CParameterDirect());
    A_param->SetValue(a);
    B_param->SetValue(b);
    // create mov operation with modifier
    std::unique_ptr<COperation> op(new COperationSLT());
    op->SetModifier(mod);
    // create mov instruction
    std::unique_ptr<CInstruction> ret(new CInstruction());
    ret->SetOperation(std::move(op));
    ret->SetAParameter(std::move(A_param));
    ret->SetBParameter(std::move(B_param));
    return ret;
}