#pragma once

#include "Operation.h"


///
/// Class representing JMZ operation.
/// Depending on modifier type, operation compares A/B or both numbers
/// of instruction with zero. If number is equal to zero, PC jumps to proper line,
/// if not move forward one operation
///
class COperationJMZ : public COperation {
public:
    COperationJMZ();
    COperationJMZ(const COperationJMZ& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};