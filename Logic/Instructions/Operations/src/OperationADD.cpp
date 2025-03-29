#include "OperationADD.h"

COperationADD::COperationADD()
{
    m_name = "ADD";
}

bool COperationADD::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
