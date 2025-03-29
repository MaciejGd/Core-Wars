#pragma once

#include "Operation.h"



class COperationDJN : public COperation {
public:
    COperationDJN();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};