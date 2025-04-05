#pragma once

#include "Operation.h"



class COperationDAT : public COperation {
public:
    COperationDAT();
    COperationDAT(const COperationDAT& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;
    
    InstructionResult Execute(int a_pointer, int b_pointer, int& pc) override;
};