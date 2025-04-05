#pragma once 

#include "Instruction.h"
#include "operator_test.h"

class JMZOperatorTest : public OperatorTest {
public:
    void RunTests() override;
private:
    void m_testA();
    void m_testBA();
    void m_testB();
    void m_testAB();
    void m_testX();
    void m_testI();
    void m_testF();
    void m_Atests(ModifierType mod);
    void m_Btests(ModifierType mod);
    void m_DoubleParamCheck(ModifierType mod);

    std::unique_ptr<CInstruction> CreateJMZPtr(int a, int b, ModifierType mod);
};