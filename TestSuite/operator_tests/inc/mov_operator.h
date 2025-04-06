#pragma once

#include <memory>
#include "Parameter.h"
#include "Instruction.h"
#include "operator_test.h"

class CInstruction;

class MOVOperatorTest : public IOperatorTest {
public:
    void RunTests() override;
private:
    void m_test_A();
    void m_test_B();
    void m_test_AB();
    void m_test_BA();
    void m_test_F();
    void m_test_I();
    void m_test_X();

    std::unique_ptr<CInstruction> CreateMovPtr(int a, int b, ModifierType mod);
};