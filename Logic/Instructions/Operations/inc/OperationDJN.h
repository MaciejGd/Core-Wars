#pragma once

#include "Operation.h"


///
/// Class representing DJN operation. 
/// DJN (Decrement Jump if Not zero), decrements value and
/// then tests if its value equal to zero. If yes, 
/// program counter is incremented by one, if not jump to address
/// pointed by A.
///
class COperationDJN : public COperation {
public:
    COperationDJN();
    COperationDJN(const COperationDJN& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;
    
    InstructionResult Execute(int a_pointer, int b_pointer, int& pc, int &modified_cell) override;
};