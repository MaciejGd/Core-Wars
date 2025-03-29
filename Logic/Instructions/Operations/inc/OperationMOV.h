#pragma once

#include "Operation.h"



class COperationMOV : public COperation {
public:
    COperationMOV();
    COperationMOV(const COperationMOV& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};