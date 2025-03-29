#include "OperationJMZ.h"

COperationJMZ::COperationJMZ()
{
    m_name = "JMZ";
}

bool COperationJMZ::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
