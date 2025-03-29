#include "OperationDIV.h"

COperationDIV::COperationDIV()
{
    m_name = "DIV";
}

bool COperationDIV::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
