#include "OperationSEQ.h"

COperationSEQ::COperationSEQ()
{
    m_name = "SEQ";
}

bool COperationSEQ::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
