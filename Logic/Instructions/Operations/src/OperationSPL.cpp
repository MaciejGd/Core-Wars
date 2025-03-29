#include "OperationSPL.h"

COperationSPL::COperationSPL()
{
    m_name = "SPL";
}

std::unique_ptr<COperation> COperationSPL::clone() const
{
    return std::unique_ptr<COperation>(new COperationSPL{*this});
}

bool COperationSPL::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
