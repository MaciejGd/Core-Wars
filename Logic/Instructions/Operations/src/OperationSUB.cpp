#include "OperationSUB.h"

COperationSUB::COperationSUB()
{
    m_name = "SUB";
}

std::unique_ptr<COperation> COperationSUB::clone() const
{
    return std::unique_ptr<COperation>(new COperationSUB{*this});
}

bool COperationSUB::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
