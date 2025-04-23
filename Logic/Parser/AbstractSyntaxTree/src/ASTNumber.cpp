#include "ASTNumber.h"


ParseResult CASTNumber::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg)
{
    Token& next_token = tokens.front();
    tokens.pop_front();
    if (next_token.type() == TokenType::NUMERICAL_VAL)
    {
        return ParseResult::PARSE_OK;
    }
    PARSING_FAIL(CLexer::s_file_name, next_token);
    LOG_ERR("Numerical value expected, got: {}", next_token.PrintFormat());

    error_msg = std::format("In line {}, idx {}, Numerical value expected, got \"{}\"",  
        next_token.line(), next_token.idx(), next_token.value());

    return ParseResult::PARSE_FAIL;
}