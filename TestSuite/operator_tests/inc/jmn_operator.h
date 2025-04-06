#pragma once 

#include "Instruction.h"
#include "operator_test.h"

class JMNOperatorTest : public IOperatorTest {
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

    static std::unique_ptr<CInstruction> CreateJMNPtr(int a, int b, ModifierType mod);
};