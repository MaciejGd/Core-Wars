#include "ASTClosingBracket.h"

ParseResult CASTClosingBracket::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes)
{
    Token& next_token = tokens.front();
    tokens.pop_front();
    if (next_token.value() == ")") 
    {
        return ParseResult::PARSE_OK;
    }
    LOG_ERR("Error in parsing file {}, in line {}, idx {}", Lexer::s_file_name, next_token.line(), next_token.idx());
    LOG_ERR("Token should be closing bracket but is {}", next_token.PrintFormat());
    return ParseResult::PARSE_FAIL;
}