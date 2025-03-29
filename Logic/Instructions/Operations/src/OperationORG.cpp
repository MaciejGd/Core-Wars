#include "OperationORG.h"

COperationORG::COperationORG()
{
    m_name = "ORG";
}

bool COperationORG::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
