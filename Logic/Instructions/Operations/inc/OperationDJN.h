#pragma once

#include "Operation.h"


///
/// Class representing DJN operation. 
/// DJN (Decrement Jum if Not zero), decrements B value and
/// the B target, then tests if B value is zero. If yes, next
/// program counter is incremented by one, if not jump to address
/// pointed by A.
///
class COperationDJN : public COperation {
public:
    COperationDJN();
    COperationDJN(const COperationDJN& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;
    
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};