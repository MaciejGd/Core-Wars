#pragma once

#include "Operation.h"



class COperationDAT : public COperation {
public:
    COperationDAT();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};