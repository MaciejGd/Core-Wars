#pragma once

#include "Operation.h"



class COperationMOD : public COperation {
public:
    COperationMOD();
    COperationMOD(const COperationMOD& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};