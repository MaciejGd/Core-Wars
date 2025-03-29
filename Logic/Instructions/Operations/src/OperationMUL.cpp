#include "OperationMUL.h"

COperationMUL::COperationMUL()
{
    m_name = "MUL";
}

std::unique_ptr<COperation> COperationMUL::clone() const
{
    return std::unique_ptr<COperation>(new COperationMUL{*this});
}

bool COperationMUL::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
