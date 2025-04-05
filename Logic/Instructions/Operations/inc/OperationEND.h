#pragma once

#include "Operation.h"



class COperationEND : public COperation {
public:
    COperationEND();
    COperationEND(const COperationEND& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;
    
    InstructionResult Execute(int a_pointer, int b_pointer, int& pc) override;
};