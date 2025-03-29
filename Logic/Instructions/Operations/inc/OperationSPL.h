#pragma once

#include "Operation.h"



class COperationSPL : public COperation {
public:
    COperationSPL();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};