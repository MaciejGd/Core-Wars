#include "OperationADD.h"

COperationADD::COperationADD()
{
    m_name = "ADD";
}

std::unique_ptr<COperation> COperationADD::clone() const
{
    return std::unique_ptr<COperation>(new COperationADD{*this});
}

bool COperationADD::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
