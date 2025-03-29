#include "OperationMOD.h"

COperationMOD::COperationMOD()
{
    m_name = "MOD";
}

bool COperationMOD::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
