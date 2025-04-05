#pragma once

#include "Operation.h"



class COperationSUB : public COperation {
public:
    COperationSUB();
    COperationSUB(const COperationSUB& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(int a_pointer, int b_pointer, int& pc) override;
};