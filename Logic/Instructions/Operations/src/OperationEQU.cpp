#include "OperationEQU.h"

COperationEQU::COperationEQU()
{
    m_name = "EQU";
}

bool COperationEQU::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
