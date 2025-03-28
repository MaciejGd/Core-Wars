#include "CodeBuilder.h"
#include "Token.h"

CCodeBuilder::CCodeBuilder(std::string file_name)
{
    m_file_name = file_name;   
}

bool CCodeBuilder::ProduceInstructions()
{
    // make sure to clean any previous instructions from m_instructions vector
    m_instructions.clear();
    // if processing file failed
    if (m_ProcessProgramFile() == false)
    {
        LOG_ERR("Failed to create instructions from file {}", m_file_name);
        return false;
    }
    LOG_DBG("Properly created instructions from file {}", m_file_name);
    return true;
}

bool CCodeBuilder::m_ProcessProgramFile()
{
    TokenContainer tokens = m_lexer.GetTokens(m_file_name);
    if (CParser::ParseFile(tokens, m_instructions) != ParseResult::PARSE_OK)
    {
        return false;
    }
    return true;
}


