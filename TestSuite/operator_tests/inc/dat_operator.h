#pragma once

#include "operator_test.h"

class DATOperatorTest : public IOperatorTest {
public: 
    void RunTests() override;

private:
    // only two tests as all modifiers should immediately fail
    void m_test();
};