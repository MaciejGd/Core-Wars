#include "OperationSEQ.h"

COperationSEQ::COperationSEQ()
{
    m_name = "SEQ";
}

std::unique_ptr<COperation> COperationSEQ::clone() const
{
    return std::unique_ptr<COperation>(new COperationSEQ{*this});
}

bool COperationSEQ::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
