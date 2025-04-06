#include "default_mod_setter.h"
#include "OperationADD.h"
#include "OperationMOV.h"
#include "OperationSLT.h"
#include "OperationDAT.h"
#include "OperationJMN.h"
#include "ParameterDirect.h"
#include "ParameterImmediate.h"
#include "ParameterIndirect.h"
#include "ParameterPostInc.h"
#include "ParameterPreDecr.h"
#include "Instruction.h"
#include "logger.h"

void DefaultModSetterTests::RunTests()
{
    m_testADD();
    m_testDAT();
    m_testJMN();
    m_testMOV();
    m_testSLT();
}

void DefaultModSetterTests::m_testMOV()
{
    LOG_WRN("Testing MOV operation");
    m_testGeneric(std::make_unique<COperationMOV>(), ModifierType::AB, ModifierType::B, ModifierType::I);
}

void DefaultModSetterTests::m_testDAT()
{
    LOG_WRN("Testing DAT operation");
    m_testGeneric(std::make_unique<COperationDAT>(), ModifierType::F, ModifierType::F, ModifierType::F);
}

void DefaultModSetterTests::m_testADD()
{
    LOG_WRN("Testing arithm operations");
    m_testGeneric(std::make_unique<COperationADD>(), ModifierType::AB, ModifierType::B, ModifierType::F);
}

void DefaultModSetterTests::m_testJMN()
{
    LOG_WRN("Testing JMN operation");
    m_testGeneric(std::make_unique<COperationJMN>(), ModifierType::B, ModifierType::B, ModifierType::B);
}

void DefaultModSetterTests::m_testSLT()
{
    LOG_WRN("Testing SLT operation");
    m_testGeneric(std::make_unique<COperationSLT>(), ModifierType::AB, ModifierType::B, ModifierType::B);
}

void DefaultModSetterTests::m_testGeneric(std::unique_ptr<COperation> op, ModifierType res1, ModifierType res2, ModifierType res3)
{
    // create mov instruction
    std::unique_ptr<CInstruction> ret(new CInstruction());
    ret->SetOperation(std::move(op));
    ret->SetAParameter(std::make_unique<CParameterImmediate>());
    ret->SetBParameter(std::make_unique<CParameterDirect>());
    // A param set to indirect, should add modifier AB
    ret->DeduceDefaultModifier();
    if (ret->GetModifier() == res1)
    {   
        LOG_PASS("Correctly deduced modifier type for instruction: {}", ret->PrintInstruction());
    }
    else {
        LOG_FAIL("Incorrectly deduced modifier type for instruction: {}, should be {}", ret->PrintInstruction(), ModifierToString(res1));
    }
    ret->SetModifier(ModifierType::DEFAULT);
    ret->SetAParameter(std::make_unique<CParameterDirect>());
    ret->SetBParameter(std::make_unique<CParameterImmediate>());
    ret->DeduceDefaultModifier();
    if (ret->GetModifier() == res2)
    {   
        LOG_PASS("Correctly deduced modifier type for instruction: {}", ret->PrintInstruction());
    }
    else {
        LOG_FAIL("Incorrectly deduced modifier type for instruction: {}, should be {}", ret->PrintInstruction(), ModifierToString(res2));
    }
    ret->SetModifier(ModifierType::DEFAULT);
    ret->SetBParameter(std::make_unique<CParameterDirect>());
    ret->DeduceDefaultModifier();
    if (ret->GetModifier() == res3)
    {   
        LOG_PASS("Correctly deduced modifier type for instruction: {}", ret->PrintInstruction());
    }
    else {
        LOG_FAIL("Incorrectly deduced modifier type for instruction: {}, should be {}", ret->PrintInstruction(), ModifierToString(res3));
    }
}
