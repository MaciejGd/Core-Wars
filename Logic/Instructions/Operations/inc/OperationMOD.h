#pragma once

#include "Operation.h"


/// Class implementing RedCode MOD operation.
/// Perform modulo operation. Kill process if modulo by zero.
class COperationMOD : public COperation {
public:
    COperationMOD();
    COperationMOD(const COperationMOD& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(int a_pointer, int b_pointer, int& pc, int &modified_cell) override;
};