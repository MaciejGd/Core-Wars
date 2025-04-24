#pragma once

#include "Operation.h"

/// Class implementing SPL RedCode operation.
/// Create new process starting from addresss specified 
class COperationSPL : public COperation {
public:
    COperationSPL();
    COperationSPL(const COperationSPL& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;
    
    InstructionResult Execute(int a_pointer, int b_pointer, int& pc, int &modified_cell) override;
};