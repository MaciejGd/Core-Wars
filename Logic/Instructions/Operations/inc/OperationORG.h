#pragma once

#include "Operation.h"



class COperationORG : public COperation {
public:
    COperationORG();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};