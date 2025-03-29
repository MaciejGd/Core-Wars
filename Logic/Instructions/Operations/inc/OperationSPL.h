#pragma once

#include "Operation.h"



class COperationSPL : public COperation {
public:
    COperationSPL();
    COperationSPL(const COperationSPL& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;
    
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};