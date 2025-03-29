#include "OperationJMP.h"

COperationJMP::COperationJMP()
{
    m_name = "JMP";
}

bool COperationJMP::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
