#include "OperationMUL.h"

COperationMUL::COperationMUL()
{
    m_name = "MUL";
}

bool COperationMUL::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
