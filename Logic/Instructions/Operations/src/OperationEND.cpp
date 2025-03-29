#include "OperationEND.h"

COperationEND::COperationEND()
{
    m_name = "END";
}

std::unique_ptr<COperation> COperationEND::clone() const
{
    return std::unique_ptr<COperation>(new COperationEND{*this});
}

bool COperationEND::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
