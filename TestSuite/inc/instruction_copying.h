#pragma once

#include "Instruction.h"

#include <memory>


class InstructionCopyingTest {
public:
    static void RunTests();

private:
    static void m_testInstructionCopying();
    static std::unique_ptr<CInstruction> m_CreateExampleInstruction();
};