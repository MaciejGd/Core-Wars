#include "OperationEND.h"

COperationEND::COperationEND()
{
    m_name = "END";
}

bool COperationEND::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
