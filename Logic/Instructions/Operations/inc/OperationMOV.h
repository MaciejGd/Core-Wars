#pragma once

#include "Operation.h"


///
/// Class representing MOV operation.
/// Depending on modifier type, operation copies specified
/// value from one place to another.
///
class COperationMOV : public COperation {
public:
    COperationMOV();
    COperationMOV(const COperationMOV& other):COperation(other) {}
    std::unique_ptr<COperation> clone() const override;

    bool Execute(std::unique_ptr<CParameter>& A_param, std::unique_ptr<CParameter>& B_param, int& pc) override;
};