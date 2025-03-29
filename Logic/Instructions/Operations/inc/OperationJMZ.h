#pragma once

#include "Operation.h"



class COperationJMZ : public COperation {
public:
    COperationJMZ();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};