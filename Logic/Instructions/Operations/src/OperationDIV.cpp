#include "OperationDIV.h"

COperationDIV::COperationDIV()
{
    m_name = "DIV";
}

std::unique_ptr<COperation> COperationDIV::clone() const
{
    return std::unique_ptr<COperation>(new COperationDIV{*this});
}

bool COperationDIV::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
