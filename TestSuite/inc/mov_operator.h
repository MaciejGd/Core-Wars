#pragma once

#include <memory>
#include "Parameter.h"
#include "Instruction.h"

class CInstruction;

class MOVOperatorTest {
public:
    static void RunTests();
private:
    static void m_test_A();
    static void m_test_B();
    static void m_test_AB();
    static void m_test_BA();
    static void m_test_F();
    static void m_test_I();
    static void m_test_X();

    static std::unique_ptr<CInstruction> CreateMovPtr(int a, int b, ModifierType mod);
};