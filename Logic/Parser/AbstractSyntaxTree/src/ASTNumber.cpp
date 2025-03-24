#include "ASTNumber.h"


ParseResult CASTNumber::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes)
{
    Token& next_token = tokens.front();
    tokens.pop_front();
    if (next_token.type() == TokenType::NUMERICAL_VAL)
    {
        return ParseResult::PARSE_OK; // TODO fill it in    
    }
    PARSING_FAIL(CLexer::s_file_name, next_token);
    LOG_ERR("Numerical value expected, got: {}", next_token.PrintFormat());
    return ParseResult::PARSE_FAIL;
}