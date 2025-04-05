#pragma once

#include "Operation.h"



class COperationEQU : public COperation {
public:
    COperationEQU();
    COperationEQU(const COperationEQU& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(int a_pointer, int b_pointer, int& pc) override;
};