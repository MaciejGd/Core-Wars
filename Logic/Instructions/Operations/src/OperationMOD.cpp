#include "OperationMOD.h"

COperationMOD::COperationMOD()
{
    m_name = "MOD";
}

std::unique_ptr<COperation> COperationMOD::clone() const
{
    return std::unique_ptr<COperation>(new COperationMOD{*this});
}

bool COperationMOD::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
