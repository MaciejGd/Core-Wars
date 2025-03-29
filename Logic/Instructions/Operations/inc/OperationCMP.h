#pragma once

#include "Operation.h"



class COperationCMP : public COperation {
public:
    COperationCMP();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};