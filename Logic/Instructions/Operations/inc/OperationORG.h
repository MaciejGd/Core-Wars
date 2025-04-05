#pragma once

#include "Operation.h"



class COperationORG : public COperation {
public:
    COperationORG();
    COperationORG(const COperationORG& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    InstructionResult Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};