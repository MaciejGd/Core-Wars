#include "CodeBuilder.h"
#include "Token.h"

bool CCodeBuilder::ProduceInstructions(std::string_view file_name)
{
    // make sure to clean any previous instructions from m_instructions vector
    m_file_name = file_name;
    m_instructions.clear();
    // if processing file failed
    if (m_ProcessProgramFile() == false)
    {
        LOG_ERR("Failed to create instructions from file {}", m_file_name);
        return false;
    }
    LOG_DBG("Properly created instructions from file {}", m_file_name);
    // after creating instructions default modifiers have to be switched to respective values
    m_DeduceDefaultModifiers();
    return true;
}

bool CCodeBuilder::m_ProcessProgramFile()
{
    TokenContainer tokens = m_lexer.GetTokens(m_file_name);
    if (CParser::ParseFile(tokens, m_instructions) == ParseResult::PARSE_OK)
    {
        LOG_DBG("Properly parsed file, and produced set of initial instructions");
        return true;
    }
    LOG_ERR("Failed to parse input file, didnt create set of initial instruction for a player");
    return false;
}

void CCodeBuilder::m_DeduceDefaultModifiers()
{
    for (auto& instruction : m_instructions)
    {
        instruction->DeduceDefaultModifier();
    }
}
