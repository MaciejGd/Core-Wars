#pragma once

#include "Operation.h"



class COperationDIV : public COperation {
public:
    COperationDIV();
    COperationDIV(const COperationDIV& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};