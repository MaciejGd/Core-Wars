#pragma once

#include "Instruction.h"

class DJNOperatorTest {
public:
    static void RunTests();

private:
    static void m_testA();
    static void m_testBA();
    static void m_testB();
    static void m_testAB();
    static void m_testX();
    static void m_testI();
    static void m_testF();

    static void m_Atests(ModifierType mod);
    static void m_Btests(ModifierType mod);
    static void m_DoubleParamCheck(ModifierType mod);

    static std::unique_ptr<CInstruction> CreateDJNPtr(int a, int b, ModifierType mod);
};