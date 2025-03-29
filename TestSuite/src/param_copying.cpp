#include "param_copying.h"
#include "memory"
#include "Parameter.h"
#include "ParameterDirect.h"
#include "ParameterIndirect.h"
#include "ParameterImmediate.h"
#include "ParameterPostInc.h"
#include "ParameterPreDecr.h"

#include "logger.h"

void ParamCopyingTest::TestCopying()
{
    m_test_val();
    m_test_eval();
    m_test_Name();
}

void ParamCopyingTest::m_test_val()
{
    std::unique_ptr<CParameter> test(new CParameterDirect{});
    test->SetValue(12);
    std::unique_ptr<CParameter> copied = test->clone();
    if (copied->GetValue() == test->GetValue())
    {
        LOG_PASS("Properly set copied value to 12");
    }
    else 
    {
        LOG_FAIL("Failed to set copied value to 12");
    }
    std::unique_ptr<CParameter> copied1(new CParameterIndirect());
    copied1->SetValue(32);
    copied1 = test->clone();
    if (copied1->GetValue() == test->GetValue())
    {
        LOG_PASS("Properly set copied value to 12 when reseting pointer");
    }
    else 
    {
        LOG_FAIL("Failed to set copied value to 12 when reseting pointer");
    }
}

void ParamCopyingTest::m_test_eval()
{
    std::unique_ptr<CParameter> test(new CParameterDirect{});
    std::unique_ptr<CParameter> copied1(new CParameterPreDecr());
    copied1->SetValue(32);
    copied1 = test->clone();
    test->EvaluateParameter(1);
    copied1->EvaluateParameter(1);
    if (test->GetReadPointer() == copied1->GetReadPointer())
    {
        LOG_PASS("Properly evalated read pointers");
    }
    else 
    {
        LOG_FAIL("Incorrectly evaluated read pointers");
    }
    
    if (test->GetWritePointer() == copied1->GetWritePointer())
    {
        LOG_PASS("Properly evalated write pointers");
    }
    else 
    {
        LOG_FAIL("Incorrectly evaluated write pointers");
    }
    
}

void ParamCopyingTest::m_test_Name()
{
    std::unique_ptr<CParameter> test(new CParameterDirect{});
    test->SetValue(12);
    std::unique_ptr<CParameter> copied(new CParameterImmediate());
    copied->SetValue(32);
    copied = test->clone();
    if (copied->Identify() == test->Identify())
    {
        LOG_PASS("Properly set copied value to 12");
    }
    else 
    {
        LOG_FAIL("Failed to set copied value to 12");
    }
    
}
