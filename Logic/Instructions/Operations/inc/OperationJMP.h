#pragma once

#include "Operation.h"



class COperationJMP : public COperation {
public:
    COperationJMP();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};