#pragma once

#include "Operation.h"



class COperationEQU : public COperation {
public:
    COperationEQU();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};