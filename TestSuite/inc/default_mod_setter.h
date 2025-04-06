#pragma once

#include <memory>
#include "Operation.h"

class DefaultModSetterTests {
public:
    void RunTests();
private:
    void m_testMOV();
    void m_testDAT();
    void m_testADD();
    void m_testJMN();
    void m_testSLT();   

    void m_testGeneric(std::unique_ptr<COperation> op, ModifierType res1, ModifierType res2, ModifierType res3);
};