#pragma once

#include "Operation.h"


/// Class implementing MUL RedCode operation.
/// Perform arithmetic multiplying.
class COperationMUL : public COperation {
public:
    COperationMUL();
    COperationMUL(const COperationMUL& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(int a_pointer, int b_pointer, int& pc, int &modified_cell) override;
};