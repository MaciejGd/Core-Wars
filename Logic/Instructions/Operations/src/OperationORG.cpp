#include "OperationORG.h"

COperationORG::COperationORG()
{
    m_name = "ORG";
}

std::unique_ptr<COperation> COperationORG::clone() const
{
    return std::unique_ptr<COperation>(new COperationORG{*this});
}

bool COperationORG::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
