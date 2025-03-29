#pragma once

#include "Operation.h"



class COperationJMN : public COperation {
public:
    COperationJMN();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};