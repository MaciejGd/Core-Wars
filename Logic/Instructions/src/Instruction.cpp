#include "Instruction.h"
#include "logger.h"

bool CInstruction::CreateParameter(std::unique_ptr<CParameter> param)
{
    // if A param has not been yet created, create it
    if (m_A_param == nullptr) 
    {
        m_A_param.reset(std::move(param));
        LOG_DBG("A parameter has been set as {}", m_A_param->Identify());
        return true;
    }
    // if B param has not been yet set, create it
    if (m_B_param == nullptr)
    {
        m_B_param.reset(std::move(param));
        LOG_DBG("B parameter has been set as {}", m_A_param->Identify());
        return true;
    }

    LOG_ERR("Both parameters A and B have already been initialized");
    return false;
}

bool CInstruction::CreateParamValue(int value)
{
    if (m_A_param == nullptr) 
    {
        LOG_ERR("Trying to set parameter value but A parameter has not been set yet");
        return false;
    }
    // if value of B param not yet set, set it
    if (!m_A_param->ValueIsSet())
    {
        m_A_param->SetValue(value);
        LOG_DBG("Properly set A parameter value to {}", value);
        return true;
    }
    if (m_B_param == nullptr)
    {
        LOG_ERR("Trying to set parameter value of B param but B parameter has not been set yet");
        return false;
    }
    // if value of B param not yet set, set it
    if (!m_B_param->ValueIsSet())
    {
        m_B_param->SetValue(value);
        LOG_DBG("Properly set B parameter value to {}", value);
        return true;
    }

    LOG_ERR("Trying to set parameter value but both parameters are already set");
    return false;
}

void CInstruction::SetAParameter(std::unique_ptr<CParameter> param)
{
    m_A_param.reset(std::move(param));
}

void CInstruction::SetBParameter(std::unique_ptr<CParameter> param)
{
    m_B_param.reset(std::move(param));
}


bool CInstruction::SetAParamValue(int value)
{
    if (!m_SetParamValue(m_A_param, value)) 
    {
        LOG_ERR("Failed to set A param");
        return false;
    }
    return true;
}

bool CInstruction::SetBParamValue(int value)
{
    if (!m_SetParamValue(m_B_param, value)) 
    {
        LOG_ERR("Failed to set B param");
        return false;
    }
    return true;
}


bool CInstruction::m_SetParamValue(std::unique_ptr<CParameter>& param, int value)
{
    if (param == nullptr) 
    {
        LOG_ERR("Trying to set parameter value but parameter is nullptr");
        return false;
    }
    param->SetValue(value);
    return true;
}
