#pragma once 

#include "Instruction.h"

class JMPOperatorTest {
public:
    static void RunTests();
private:
    static void m_testA();

    static std::unique_ptr<CInstruction> CreateJMPPtr(int a, int b, ModifierType mod);
};