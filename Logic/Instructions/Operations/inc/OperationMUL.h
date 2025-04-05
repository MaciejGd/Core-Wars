#pragma once

#include "Operation.h"



class COperationMUL : public COperation {
public:
    COperationMUL();
    COperationMUL(const COperationMUL& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(int a_pointer, int b_pointer, int& pc) override;
};