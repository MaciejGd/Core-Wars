#include "OperationSPL.h"

COperationSPL::COperationSPL()
{
    m_name = "SPL";
}

bool COperationSPL::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
