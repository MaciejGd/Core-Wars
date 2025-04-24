#pragma once

#include "Operation.h"



/// Class implementing RedCode JMP operation.
/// Jump to specified memmory address.
class COperationJMP : public COperation {
public:
    COperationJMP();
    COperationJMP(const COperationJMP& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;
    
    InstructionResult Execute(int a_pointer, int b_pointer, int& pc, int &modified_cell) override;
};