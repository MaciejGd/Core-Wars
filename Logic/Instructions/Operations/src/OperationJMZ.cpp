#include "OperationJMZ.h"

COperationJMZ::COperationJMZ()
{
    m_name = "JMZ";
}

std::unique_ptr<COperation> COperationJMZ::clone() const
{
    return std::unique_ptr<COperation>(new COperationJMZ{*this});
}

bool COperationJMZ::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
