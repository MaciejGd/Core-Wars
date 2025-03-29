#pragma once

#include "Operation.h"



class COperationJMZ : public COperation {
public:
    COperationJMZ();
    COperationJMZ(const COperationJMZ& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};