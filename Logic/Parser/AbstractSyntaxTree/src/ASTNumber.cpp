#include "ASTNumber.h"


ParseResult CASTNumber::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes)
{
    Token& next_token = tokens.front();
    tokens.pop_front();
    if (next_token.type() == TokenType::NUMERICAL_VAL)
    {
        return ParseResult::PARSE_OK; // TODO fill it in    
    }
    LOG_ERR("Error in parsign file {}, in line {}, idx {}", Lexer::s_file_name, next_token.line(), next_token.idx());
    LOG_ERR("Numerical value expected, got: {}", next_token.PrintFormat());
    return ParseResult::PARSE_FAIL;
}