#pragma once

#include "Operation.h"



class COperationCMP : public COperation {
public:
    COperationCMP();
    COperationCMP(const COperationCMP& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(int a_pointer, int b_pointer, int& pc) override;
};