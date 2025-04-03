#pragma once

#include "Instruction.h"

class SLTOperatorTest {
public:
    static void RunTests();

private:
    static void m_testA();
    static void m_testB();
    static void m_testBA();
    static void m_testAB();
    static void m_testX();
    static void m_testF();
    static void m_testI();

    static std::unique_ptr<CInstruction> CreateSLTPtr(int a, int b, ModifierType mod);
};