#include "operator_copying.h"

#include <memory>
#include "Operation.h"
#include "OperationDAT.h"
#include "OperationDIV.h"
#include "OperationCMP.h"
#include "logger.h"

void OperatorCopyingTests::RunTests()
{
    m_test_operator();
    m_test_modifier();   
}

void OperatorCopyingTests::m_test_operator()
{
    std::unique_ptr<COperation> test(new COperationCMP{});
    std::unique_ptr<COperation> copy(new COperationDIV{});

    copy = test->clone();
    if (copy->GetOperationName() == test->GetOperationName())
    {
        LOG_PASS("Copied name equal to og name: {}", copy->GetOperationName());
    }
    else 
    {
        LOG_FAIL("Copy failed, copy name: {}, og name: {}", copy->GetOperationName(),
                test->GetOperationName());
    }
}

void OperatorCopyingTests::m_test_modifier()
{
    std::unique_ptr<COperation> test(new COperationCMP{});
    test->SetModifier(ModifierType::I);
    std::unique_ptr<COperation> copy(new COperationDIV{});
    copy->SetModifier(ModifierType::AB);
    copy = test->clone();
    if (copy->GetModifier() == test->GetModifier())
    {
        LOG_PASS("Copied modifier equal to og modifier: {}", ModifierToString(copy->GetModifier()));
    }
    else 
    {
        LOG_FAIL("Copy failed, copy modifier: {}, og modifier: {}", ModifierToString(copy->GetModifier()),
                ModifierToString(test->GetModifier()));
    }
}
