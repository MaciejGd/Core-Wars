#include "OperationJMP.h"

COperationJMP::COperationJMP()
{
    m_name = "JMP";
}

std::unique_ptr<COperation> COperationJMP::clone() const
{
    return std::unique_ptr<COperation>(new COperationJMP{*this});
}

bool COperationJMP::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
