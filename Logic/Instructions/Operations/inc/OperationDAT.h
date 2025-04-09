#pragma once

#include "Operation.h"



/// 
/// Class representing DAT operation
/// Calling execute method of DAT operation
/// will cause killing process, no extra 
/// computations are needed
///
class COperationDAT : public COperation {
public:
    COperationDAT();
    COperationDAT(const COperationDAT& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;
    
    InstructionResult Execute(int a_pointer, int b_pointer, int& pc, int &modified_cell) override;
};