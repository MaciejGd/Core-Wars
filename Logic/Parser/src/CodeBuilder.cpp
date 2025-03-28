#include "CodeBuilder.h"
#include "Token.h"

CCodeBuilder::CCodeBuilder(std::string file_name)
{
    m_file_name = file_name;   
}

void CCodeBuilder::m_ProcessProgramFile()
{
    TokenContainer tokens = m_lexer.GetTokens(m_file_name);
    if (CParser::ParseFile(tokens, m_instructions) != ParseResult::PARSE_OK)
    {
;
    }
}


