#pragma once

#include "Operation.h"


/// Class implementing DIV RedCode operation.
/// Perform division, kill process if dividing by zero.
class COperationDIV : public COperation {
public:
    COperationDIV();
    COperationDIV(const COperationDIV& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(int a_pointer, int b_pointer, int& pc, int &modified_cell) override;
};