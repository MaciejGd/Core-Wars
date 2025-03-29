#include "OperationDAT.h"

COperationDAT::COperationDAT()
{
    m_name = "DAT";
}

bool COperationDAT::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    // executing DAT operation will lead to immediate fail
    return false;
}
