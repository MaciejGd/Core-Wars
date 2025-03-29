#include "OperationCMP.h"

COperationCMP::COperationCMP()
{
    m_name = "CMP";
}

bool COperationCMP::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
