#pragma once

#include "Operation.h"



class COperationADD : public COperation {
public:
    COperationADD();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};