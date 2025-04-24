#pragma once

#include "Operation.h"


/// Class representing MOV operation.
/// Depending on modifier type, operation copies specified
/// value from one place to another.
class COperationMOV : public COperation {
public:
    COperationMOV();
    COperationMOV(const COperationMOV& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(int a_pointer, int b_pointer, int& pc, int &modified_cell) override;
};