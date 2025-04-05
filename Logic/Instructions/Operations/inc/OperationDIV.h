#pragma once

#include "Operation.h"



class COperationDIV : public COperation {
public:
    COperationDIV();
    COperationDIV(const COperationDIV& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(int a_pointer, int b_pointer, int& pc) override;
};