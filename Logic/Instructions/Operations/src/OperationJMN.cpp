#include "OperationJMN.h"

COperationJMN::COperationJMN()
{
    m_name = "JMN";
}

std::unique_ptr<COperation> COperationJMN::clone() const
{
    return std::unique_ptr<COperation>(new COperationJMN{*this});
}

bool COperationJMN::Execute(std::unique_ptr<CParameter> &A_param, std::unique_ptr<CParameter> &B_param, int &pc)
{
    return false;
}
