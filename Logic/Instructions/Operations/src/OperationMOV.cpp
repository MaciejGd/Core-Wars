#include "OperationMOV.h"

COperationMOV::COperationMOV()
{
    m_name = "MOV";
}

bool COperationMOV::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
