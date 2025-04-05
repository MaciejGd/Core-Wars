#pragma once

#include "Operation.h"



class COperationJMP : public COperation {
public:
    COperationJMP();
    COperationJMP(const COperationJMP& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;
    
    InstructionResult Execute(int a_pointer, int b_pointer, int& pc) override;
};