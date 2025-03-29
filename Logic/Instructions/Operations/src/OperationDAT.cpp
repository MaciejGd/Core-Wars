#include "OperationDAT.h"

COperationDAT::COperationDAT()
{
    m_name = "DAT";
}

bool COperationDAT::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
