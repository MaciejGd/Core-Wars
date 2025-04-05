#pragma once

#include "Instruction.h"
#include "operator_test.h"

class CArena;

class MODOperatorTest : public OperatorTest {
public:
    void RunTests() override;

private:
    void m_testA();
    void m_testB();
    void m_testAB();
    void m_testBA();
    void m_testX();
    void m_testF();
    void m_testI();

    CArena& m_testInit(ModifierType mod);
    void m_testIF(ModifierType mod);

    std::unique_ptr<CInstruction> CreateMODPtr(int a, int b, ModifierType mod);
};