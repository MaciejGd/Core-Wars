#pragma once

#include "Operation.h"

///
/// Class representing JMN operation.
/// Depending on modifier type, operation compares A/B or both numbers
/// of instruction with zero. If number is not equal to zero, PC jumps specified line,
/// if equal move forward one operation
///
class COperationJMN : public COperation {
public:
    COperationJMN();
    COperationJMN(const COperationJMN& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(int a_pointer, int b_pointer, int& pc) override;
};