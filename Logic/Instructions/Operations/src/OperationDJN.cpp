#include "OperationDJN.h"

COperationDJN::COperationDJN()
{
    m_name = "DJN";
}

std::unique_ptr<COperation> COperationDJN::clone() const
{
    return std::unique_ptr<COperation>(new COperationDJN{*this});
}

bool COperationDJN::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
