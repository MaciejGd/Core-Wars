#pragma once

#include "Operation.h"



class COperationMUL : public COperation {
public:
    COperationMUL();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};