#include "Token.h"
#include "logger.h"
#include <algorithm>

std::string Token::m_TokenTypeToString() const
{
    switch (m_type) 
    {
        case TokenType::MODIFIERS:
            return "MODIFIERS";
        case TokenType::SEPARATOR:
            return "SEPARATOR";
        case TokenType::OPERATIONS:
            return "OPERATIONS";
        case TokenType::ADDRESS_MODE:
            return "ADDRESS_MODE";
        case TokenType::LABEL:
            return "LABEL";
        case TokenType::ARITHM_OPS:
            return "ARITHM_OPS";
        case TokenType::NUMERICAL_VAL:
            return "NUMERICAL_VAL";
        default:
            return "WRONG_TYPE";
    }
}

void Token::m_AddCategory(std::string_view lex)
{
    if (std::find(tkn_modifiers.begin(), tkn_modifiers.end(), lex) != tkn_modifiers.end()) 
    {
        m_type = TokenType::MODIFIERS;
        return;
    }
    if (std::find(tkn_operations.begin(), tkn_operations.end(), lex) != tkn_operations.end()) 
    {
        m_type = TokenType::OPERATIONS;
        return;
    }
    // check if token is numerical value
    bool numerical = true;
    for (int i = 0; i < lex.size(); i++) 
    {
        if (!std::isdigit(lex[i]))
        {
            numerical = false;
            break;
        }
    }
    if (numerical) 
    {
        m_type = TokenType::NUMERICAL_VAL;
        return;
    }
    // if none of above and size not 1 then add label
    if (lex.size() != 1) {
        m_type = TokenType::LABEL;
        return;
    } 
    if (lex[0] == tkn_coma) 
    {
        m_type = TokenType::SEPARATOR;
        return;
    }
    if (std::find(tkn_address_modes.begin(), tkn_address_modes.end(), lex[0]) != tkn_address_modes.end())
    {
        m_type = TokenType::ADDRESS_MODE;
        return;
    }
    if (std::find(tkn_ar_ops.begin(), tkn_ar_ops.end(), lex[0]) != tkn_ar_ops.end())
    {
        m_type = TokenType::ARITHM_OPS;
        return;
    }
    m_type = TokenType::LABEL;
}

Token::Token(int _line, int _idx, std::string_view lex): m_val(lex), m_line(_line), m_idx(_idx)
{
    m_AddCategory(m_val);
}

std::string Token::PrintFormat() const
{
    return "[loc:{line:" + std::to_string(m_line) + "}{idx:"+ std::to_string(m_idx) + "}]->[type:" + m_TokenTypeToString() + "|val:" + m_val + "]";
}