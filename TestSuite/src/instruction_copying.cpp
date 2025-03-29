#include "instruction_copying.h"

#include "Instruction.h"
#include "Operation.h"
#include "OperationCMP.h"
#include "Parameter.h"
#include "ParameterDirect.h"
#include "ParameterPreDecr.h"

#include "logger.h"

void InstructionCopyingTest::RunTests()
{
    m_testInstructionCopying();
}


void InstructionCopyingTest::m_testInstructionCopying()
{
    std::unique_ptr<CInstruction> test = m_CreateExampleInstruction();
    std::unique_ptr<CInstruction> copy(new CInstruction());

    copy.reset(new CInstruction{*test});

    if (test->PrintInstruction() == copy->PrintInstruction())
    {
        LOG_PASS("Successfully copied instructions, {}", test->PrintInstruction());
    }
    else 
    {
        LOG_FAIL("Failed to copy instructions, og {} => copy {}", test->PrintInstruction(), 
                    copy->PrintInstruction());
    }
}

std::unique_ptr<CInstruction> InstructionCopyingTest::m_CreateExampleInstruction()
{
    std::unique_ptr<CInstruction> test(new CInstruction());
    std::unique_ptr<COperation> op(new COperationCMP{});
    op->SetModifier(ModifierType::I);
    std::unique_ptr<CParameter> paramA(new CParameterDirect{});
    paramA->SetValue(12);

    std::unique_ptr<CParameter> paramB(new CParameterPreDecr());
    paramB->SetValue(32);

    test->SetOperation(std::move(op));
    test->SetAParameter(std::move(paramA));
    test->SetBParameter(std::move(paramB));

    return test;
}
