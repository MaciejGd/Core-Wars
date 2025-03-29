#pragma once

#include "Operation.h"



class COperationSUB : public COperation {
public:
    COperationSUB();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};