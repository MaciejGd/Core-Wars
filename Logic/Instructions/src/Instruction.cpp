#include "Instruction.h"
#include "logger.h"
#include "ParameterImmediate.h"
#include "ParameterDirect.h"
#include "OperationDAT.h"

CInstruction::CInstruction(const CInstruction& other)
{
    // clone all ptrs values if they are valid
    LOG_WRN("Copying instruction: {}", other.PrintInstruction());
    if (other.m_A_param != nullptr)
    {
        m_A_param = other.m_A_param->clone();
    }
    if (other.m_B_param != nullptr)
    {
        m_B_param = other.m_B_param->clone();
    }
    if (other.m_operation != nullptr)
    {
        m_operation = other.m_operation->clone();
    }
}

CInstruction::CInstruction(CInstruction&& other)
{
    m_A_param = std::move(other.m_A_param);
    m_B_param = std::move(other.m_B_param);
    m_operation = std::move(other.m_operation);
}

CInstruction& CInstruction::operator=(const CInstruction& other) 
{
    CInstruction copy(other);
    *this = std::move(copy);
    return *this;
}

CInstruction& CInstruction::operator=(CInstruction&& other)
{
    *this = std::move(other);
    return *this;   
}

bool CInstruction::CreateParameter(std::unique_ptr<CParameter> param)
{
    // if A param has not been yet created, create it
    if (m_A_param == nullptr) 
    {
        m_A_param = std::move(param);
        LOG_DBG("A parameter has been set as {}", m_A_param->Identify());
        return true;
    }
    // if B param has not been yet set, create it
    if (m_B_param == nullptr)
    {
        m_B_param = std::move(param);
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
    m_A_param = (std::move(param));
}

void CInstruction::SetBParameter(std::unique_ptr<CParameter> param)
{
    m_B_param = (std::move(param));
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

void CInstruction::SetOperation(std::unique_ptr<COperation> operation)
{
    if (m_operation != nullptr)
    {
        LOG_WRN("Overriding current operation: {}", m_operation->GetOperationName());
    }
    m_operation = std::move(operation);
}

bool CInstruction::SetModifier(ModifierType modifier)
{
    if (m_operation == nullptr)
    {
        LOG_ERR("Trying to set modifier value, but operation has not been set yet");
        return false;
    }
    m_operation->SetModifier(modifier);
    LOG_DBG("Value of modifier changed to: {}",  ModifierToString(modifier));
    return true;
}

void CInstruction::DeduceDefaultModifier()
{
    if (m_A_param == nullptr || m_B_param == nullptr)
    {
        LOG_ERR("Params not set yet, emergency exit");
        return;
    } 
    std::string a_param_type = "";
    std::string b_param_type = "";
    a_param_type = m_A_param->Identify();
    b_param_type = m_B_param->Identify();
    m_operation->DeduceDefaultModifier(a_param_type, b_param_type);
}

void CInstruction::FinishInstructionSetup()
{
    // need to add this function as according to spec, B parameter is optional
    if (m_B_param == nullptr)
    {
        m_B_param = std::make_unique<CParameterDirect>(0);
    }
}

std::string CInstruction::PrintInstruction() const
{
    if (m_operation == nullptr)
    {
        return "Operation for instruction has not been yet set!";
    }
    if (m_A_param == nullptr)
    {
        return "Parameter A for instruction has not been yet set";
    }
    std::string instruction_str = m_operation->GetOperationName() + "." + 
                                    ModifierToString(m_operation->GetModifier());
    instruction_str += ( "  " + m_A_param->Identify() + " " + std::to_string(m_A_param->GetValue()));
    if (m_B_param)
    {
        instruction_str += ( ", " + m_B_param->Identify() + " " + std::to_string(m_B_param->GetValue()));
    }
    return instruction_str;
}

std::unique_ptr<CInstruction> CInstruction::CreateDefaultInstruction()
{
    std::unique_ptr<CParameter> A_param(new CParameterImmediate());
    std::unique_ptr<CParameter> B_param(new CParameterImmediate());
    A_param->SetValue(0);
    B_param->SetValue(0);
    std::unique_ptr<COperation> op(new COperationDAT());
    op->SetModifier(ModifierType::F);
    // create instruction
    std::unique_ptr<CInstruction> ret(new CInstruction());
    ret->SetOperation(std::move(op));
    ret->SetAParameter(std::move(A_param));
    ret->SetBParameter(std::move(B_param));
    return std::move(ret);
}

InstructionResult CInstruction::Execute(int &pc)
{
    if (m_A_param == nullptr || m_B_param == nullptr || m_operation == nullptr)
    {
        LOG_ERR("Parameters are invalid for instruction at index {}", pc);
        return InstructionResult::FAIL;
    } 
    // at first evaluate both parameters
    m_A_param->EvaluateParameter(pc);
    m_B_param->EvaluateParameter(pc);
    // then execute operation
    int a_pointer = m_A_param->GetPointer();
    int b_pointer = m_B_param->GetPointer();
    return m_operation->Execute(a_pointer, b_pointer, pc);
}

bool CInstruction::m_SetParamValue(std::unique_ptr<CParameter> &param, int value)
{
    if (param == nullptr) 
    {
        LOG_ERR("Trying to set parameter value but parameter is nullptr");
        return false;
    }
    param->SetValue(value);
    return true;
}

