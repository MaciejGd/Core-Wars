#pragma once

#include "Operation.h"



class COperationADD : public COperation {
public:
    COperationADD();
    COperationADD(const COperationADD& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;
    
    InstructionResult Execute(int a_pointer, int b_pointer, int& pc, int &modified_cell) override;
};