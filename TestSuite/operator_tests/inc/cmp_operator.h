#pragma once

#include "Instruction.h"
#include "operator_test.h"

class CMPOperatorTest : public OperatorTest{
public:
    void RunTests();

private:
    void m_testA();
    void m_testB();
    void m_testBA();
    void m_testAB();
    void m_testX();
    void m_testF();
    void m_testI();

    std::unique_ptr<CInstruction> CreateCMPPtr(int a, int b, ModifierType mod);
};