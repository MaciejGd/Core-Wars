#include "operations_test_machine.h"
#include "add_operator.h"
#include "cmp_operator.h"
#include "dat_operator.h"
#include "div_operator.h"
#include "djn_operator.h"
#include "jmn_operator.h"
#include "jmp_operator.h"
#include "jmz_operator.h"
#include "mod_operator.h"
#include "mov_operator.h"
#include "mul_operator.h"
#include "slt_operator.h"
#include "sub_operator.h"

OperationTestingMachine::OperationTestingMachine()
{
    m_tests[0] = std::make_unique<ADDOperatorTest>();
    m_tests[1] = std::make_unique<CMPOperatorTest>();
    m_tests[2] = std::make_unique<DATOperatorTest>();
    m_tests[3] = std::make_unique<DIVOperatorTest>();
    m_tests[4] = std::make_unique<DJNOperatorTest>();
    m_tests[5] = std::make_unique<JMNOperatorTest>();
    m_tests[6] = std::make_unique<JMPOperatorTest>();
    m_tests[7] = std::make_unique<JMZOperatorTest>();
    m_tests[8] = std::make_unique<MODOperatorTest>();
    m_tests[9] = std::make_unique<MOVOperatorTest>();
    m_tests[10] = std::make_unique<MULOperatorTest>();
    m_tests[11] = std::make_unique<SLTOperatorTest>();
    m_tests[12] = std::make_unique<SUBOperatorTest>();
}

void OperationTestingMachine::RunTests()
{
    // execute all tests
    for (auto &x : m_tests)
    {
        x->RunTests();
    }
}
