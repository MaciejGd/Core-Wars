#include "OperationCMP.h"

COperationCMP::COperationCMP()
{
    m_name = "CMP";
}

std::unique_ptr<COperation> COperationCMP::clone() const
{
    return std::unique_ptr<COperation>(new COperationCMP{*this});
}

bool COperationCMP::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
