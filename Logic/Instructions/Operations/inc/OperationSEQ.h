#pragma once

#include "Operation.h"



class COperationSEQ : public COperation {
public:
    COperationSEQ();
    COperationSEQ(const COperationSEQ& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};