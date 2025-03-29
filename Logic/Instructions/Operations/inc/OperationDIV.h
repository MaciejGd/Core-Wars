#pragma once

#include "Operation.h"



class COperationDIV : public COperation {
public:
    COperationDIV();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};