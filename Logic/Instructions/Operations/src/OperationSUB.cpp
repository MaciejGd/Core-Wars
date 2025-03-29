#include "OperationSUB.h"

COperationSUB::COperationSUB()
{
    m_name = "SUB";
}

bool COperationSUB::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
