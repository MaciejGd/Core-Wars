#include "mov_operator.h"
#include "Arena.h"
#include "ParameterImmediate.h"
#include "ParameterDirect.h"
#include "OperationMOV.h"
#include "Instruction.h"
#include "logger.h"

#define STARTING_ADDRESS 100
#define A_VAL 10
#define B_VAL 20

void MOVOperatorTest::RunTests()
{
    m_test_A();
    m_test_B();
    m_test_AB();
    m_test_BA();
    m_test_F();
    m_test_X();
    m_test_I();
}

void MOVOperatorTest::m_test_A()
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    int D_STARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = std::move(CreateMovPtr(A_VAL, B_VAL, ModifierType::A));
    LOG_DBG("Instruction in Address {} is: {}", STARTING_ADDRESS, arena[STARTING_ADDRESS]->PrintInstruction());
    if (!arena[STARTING_ADDRESS]->Execute(D_STARTING_ADDRESS))
    {
        LOG_FAIL("Failed to executed instruction");
        return;
    }
    
    if (arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == A_VAL && arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == 0)
    {
        LOG_PASS("A field of instruction in PC+WPB has been modified, instruction: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("A field of instruction in PC+WPB has not been modified, instruction: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    
    int counter = 0;
    for (int i = 0; i < ARENA_SIZE; i++)
    {
        if (arena[i]->GetAParamValue() != 0) counter++;
    }
    
    if (counter != 2)
    {
        LOG_FAIL("Some other instruction has been modified and it shouldnt");
    }
    else 
    {
        LOG_PASS("No other instructions has been modfied");
    }
}

void MOVOperatorTest::m_test_B()
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    int D_STARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = std::move(CreateMovPtr(A_VAL, B_VAL, ModifierType::X));
    LOG_DBG("Instruction in Address {} is: {}", STARTING_ADDRESS, arena[STARTING_ADDRESS]->PrintInstruction());

    if (!arena[STARTING_ADDRESS]->Execute(D_STARTING_ADDRESS))
    {
        LOG_FAIL("Failed to executed instruction");
        return;
    }
    
    if (arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == B_VAL && arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == A_VAL)
    {
        LOG_PASS("A and B field of instruction in PC+WPB has been modified, instruction: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("A and B field of instruction in PC+WPB has not been modified, instruction in PC+WPB: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    
    int counter = 0;
    for (int i = 0; i < ARENA_SIZE; i++)
    {
        if (arena[i]->GetBParamValue() != 0 && arena[i]->GetAParamValue() != 0) {
            counter++;
        }
    }

    if (counter != 2)
    {
        LOG_FAIL("Some other instruction has been modified and it shouldnt");
    }
    else 
    {
        LOG_PASS("No other instructions has been modfied");
    }
}

void MOVOperatorTest::m_test_AB()
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    int D_STARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = std::move(CreateMovPtr(A_VAL, B_VAL, ModifierType::AB));
    LOG_DBG("Instruction in Address {} is: {}", STARTING_ADDRESS, arena[STARTING_ADDRESS]->PrintInstruction());

    if (!arena[STARTING_ADDRESS]->Execute(D_STARTING_ADDRESS))
    {
        LOG_FAIL("Failed to executed instruction");
        return;
    }
    
    if (arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == A_VAL && arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == 0)
    {
        LOG_PASS("B field of instruction in PC+WPB has been modified to A val, instruction: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("B field of instruction in PC+WPB has not been modified, instruction in PC+WPB: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    
    int counter = 0;
    for (int i = 0; i < ARENA_SIZE; i++)
    {
        if (arena[i]->GetBParamValue() != 0) {
            counter++;
        }
    }
    
    if (counter != 2)
    {
        LOG_FAIL("Some other instruction has been modified and it shouldnt");
    }
    else 
    {
        LOG_PASS("No other instructions has been modfied");
    }
}

void MOVOperatorTest::m_test_BA()
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    int D_STARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = std::move(CreateMovPtr(A_VAL, B_VAL, ModifierType::BA));
    LOG_DBG("Instruction in Address {} is: {}", STARTING_ADDRESS, arena[STARTING_ADDRESS]->PrintInstruction());

    if (!arena[STARTING_ADDRESS]->Execute(D_STARTING_ADDRESS))
    {
        LOG_FAIL("Failed to executed instruction");
        return;
    }
    
    if (arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == B_VAL && arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == 0)
    {
        LOG_PASS("A field of instruction in PC+WPB has been modified with B val, instruction: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("B field of instruction in PC+WPB has not been modified, instruction in PC+WPB: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    
    int counter = 0;
    for (int i = 0; i < ARENA_SIZE; i++)
    {
        if (arena[i]->GetAParamValue() != 0) {
            counter++;
        }
    }
    
    if (counter != 2)
    {
        LOG_FAIL("Some other instruction has been modified and it shouldnt");
    }
    else 
    {
        LOG_PASS("No other instructions has been modfied");
    }
}

void MOVOperatorTest::m_test_F()
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    int D_STARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = std::move(CreateMovPtr(A_VAL, B_VAL, ModifierType::F));
    LOG_DBG("Instruction in Address {} is: {}", STARTING_ADDRESS, arena[STARTING_ADDRESS]->PrintInstruction());

    if (!arena[STARTING_ADDRESS]->Execute(D_STARTING_ADDRESS))
    {
        LOG_FAIL("Failed to executed instruction");
        return;
    }
    
    if (arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == A_VAL && arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == B_VAL)
    {
        LOG_PASS("A and B field of instruction in PC+WPB has been modified, instruction: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("A and B field of instruction in PC+WPB has not been modified, instruction in PC+WPB: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    
    int counter = 0;
    for (int i = 0; i < ARENA_SIZE; i++)
    {
        if (arena[i]->GetBParamValue() != 0 && arena[i]->GetAParamValue() != 0) {
            counter++;
        }
    }
    
    if (counter != 2)
    {
        LOG_FAIL("Some other instruction has been modified and it shouldnt");
    }
    else 
    {
        LOG_PASS("No other instructions has been modfied");
    }
}

void MOVOperatorTest::m_test_X()
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    int D_STARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = std::move(CreateMovPtr(A_VAL, B_VAL, ModifierType::X));
    LOG_DBG("Instruction in Address {} is: {}", STARTING_ADDRESS, arena[STARTING_ADDRESS]->PrintInstruction());

    if (!arena[STARTING_ADDRESS]->Execute(D_STARTING_ADDRESS))
    {
        LOG_FAIL("Failed to executed instruction");
        return;
    }
    
    if (arena[STARTING_ADDRESS+B_VAL]->GetAParamValue() == B_VAL && arena[STARTING_ADDRESS+B_VAL]->GetBParamValue() == A_VAL)
    {
        LOG_PASS("A and B field of instruction in PC+WPB has been modified, instruction: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("A and B field of instruction in PC+WPB has not been modified, instruction in PC+WPB: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    
    int counter = 0;
    for (int i = 0; i < ARENA_SIZE; i++)
    {
        if (arena[i]->GetBParamValue() != 0 && arena[i]->GetAParamValue() != 0) {
            counter++;
        }
    }
    
    if (counter != 2)
    {
        LOG_FAIL("Some other instruction has been modified and it shouldnt");
    }
    else 
    {
        LOG_PASS("No other instructions has been modfied");
    }
}

void MOVOperatorTest::m_test_I()
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    int D_STARTING_ADDRESS = STARTING_ADDRESS;
    arena[STARTING_ADDRESS] = std::move(CreateMovPtr(A_VAL, B_VAL, ModifierType::I));
    LOG_DBG("Instruction in Address {} is: {}", STARTING_ADDRESS, arena[STARTING_ADDRESS]->PrintInstruction());

    if (!arena[STARTING_ADDRESS]->Execute(D_STARTING_ADDRESS))
    {
        LOG_FAIL("Failed to executed instruction");
        return;
    }
    if (arena[STARTING_ADDRESS+B_VAL]->PrintInstruction() == arena[STARTING_ADDRESS]->PrintInstruction())
    {
        LOG_PASS("Instruction properly copied to field PC+WPB has been modified, instruction: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Copying instruction to PC+WPB has failed, instruction in PC+WPB: {}", arena[STARTING_ADDRESS+B_VAL]->PrintInstruction());
    }
    
    int counter = 0;
    for (int i = 0; i < ARENA_SIZE; i++)
    {
        if (arena[i]->GetBParamValue() != 0 && arena[i]->GetAParamValue() != 0) {
            counter++;
        }
    }
    
    if (counter != 2)
    {
        LOG_FAIL("Some other instruction has been modified and it shouldnt");
    }
    else 
    {
        LOG_PASS("No other instructions has been modfied");
    } 
}


std::unique_ptr<CInstruction> MOVOperatorTest::CreateMovPtr(int a, int b, ModifierType mod)
{
    // create params with immediate addressing
    std::unique_ptr<CParameter> A_param(new CParameterImmediate());
    std::unique_ptr<CParameter> B_param(new CParameterDirect());
    A_param->SetValue(a);
    B_param->SetValue(b);
    // create mov operation with modifier
    std::unique_ptr<COperation> op(new COperationMOV());
    op->SetModifier(mod);
    // create mov instruction
    std::unique_ptr<CInstruction> ret(new CInstruction());
    ret->SetOperation(std::move(op));
    ret->SetAParameter(std::move(A_param));
    ret->SetBParameter(std::move(B_param));
    return ret;
}
