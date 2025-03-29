#pragma once

#include "Operation.h"



class COperationEND : public COperation {
public:
    COperationEND();
    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};