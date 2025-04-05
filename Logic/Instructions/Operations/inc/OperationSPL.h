#pragma once

#include "Operation.h"



class COperationSPL : public COperation {
public:
    COperationSPL();
    COperationSPL(const COperationSPL& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;
    
    InstructionResult Execute(int a_pointer, int b_pointer, int& pc) override;
};