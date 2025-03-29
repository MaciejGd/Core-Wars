#include "OperationDAT.h"

COperationDAT::COperationDAT()
{
    m_name = "DAT";
}

std::unique_ptr<COperation> COperationDAT::clone() const
{
    return std::unique_ptr<COperation>(new COperationDAT{*this});
}

bool COperationDAT::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    // executing DAT operation will lead to immediate fail
    return false;
}
