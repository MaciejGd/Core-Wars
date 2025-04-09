#pragma once

#include "operator_test.h"

#include <array>
#include <memory>


class OperationTestingMachine {
public:
    OperationTestingMachine();
    void RunTests();

private:
    std::array<std::unique_ptr<IOperatorTest>, 13> m_tests;

};