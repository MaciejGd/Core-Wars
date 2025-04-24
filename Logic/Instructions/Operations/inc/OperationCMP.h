#pragma once

#include "Operation.h"


/// Class implementing CMP RedCode operation.
/// Compare two values, jump 2 cells if comparing succeed
class COperationCMP : public COperation {
public:
    COperationCMP();
    COperationCMP(const COperationCMP& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(int a_pointer, int b_pointer, int& pc, int &modified_cell) override;
};