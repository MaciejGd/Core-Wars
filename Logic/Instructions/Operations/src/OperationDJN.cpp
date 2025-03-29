#include "OperationDJN.h"

COperationDJN::COperationDJN()
{
    m_name = "DJN";
}

bool COperationDJN::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
