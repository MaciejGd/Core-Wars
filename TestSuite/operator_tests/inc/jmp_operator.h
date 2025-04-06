#pragma once 

#include "Instruction.h"
#include "operator_test.h"

class JMPOperatorTest : public IOperatorTest {
public:
    void RunTests();
private:
    void m_testA();

    std::unique_ptr<CInstruction> CreateJMPPtr(int a, int b, ModifierType mod);
};