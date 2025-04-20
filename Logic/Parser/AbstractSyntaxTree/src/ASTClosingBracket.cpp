#include "ASTClosingBracket.h"

ParseResult CASTClosingBracket::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg)
{
    Token& next_token = tokens.front();
    tokens.pop_front();
    if (next_token.value() == ")") 
    {
        return ParseResult::PARSE_OK;
    }
    PARSING_FAIL(CLexer::s_file_name, next_token);
    LOG_ERR("Token should be closing bracket but is {}", next_token.PrintFormat());
    error_msg = std::format("In line {}, idx {}, token should be closing bracket but is \"{}\"",  
            next_token.line(), next_token.idx(), next_token.value());
    return ParseResult::PARSE_FAIL;
}