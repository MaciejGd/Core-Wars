#pragma once

#include "Operation.h"



class COperationDAT : public COperation {
public:
    COperationDAT();
    COperationDAT(const COperationDAT& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;
    
    InstructionResult Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};