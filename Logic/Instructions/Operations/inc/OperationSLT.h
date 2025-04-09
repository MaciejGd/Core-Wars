#pragma once

#include "Operation.h"



class COperationSLT : public COperation {
public:
    COperationSLT();
    COperationSLT(const COperationSLT& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(int a_pointer, int b_pointer, int& pc, int &modified_cell) override;
};