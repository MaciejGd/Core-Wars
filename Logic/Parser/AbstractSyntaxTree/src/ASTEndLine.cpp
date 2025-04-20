#include "ASTEndLine.h"

ParseResult CASTEndLine::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg)
{
    Token& next_token = tokens.front();
    tokens.pop_front();
    if (next_token.type() == TokenType::END_LINE)
    {
        return ParseResult::PARSE_OK;
    }
    // log error
    PARSING_FAIL(CLexer::s_file_name, next_token);
    LOG_ERR("EndLine token expected but present token is {}", next_token.PrintFormat());
    // set error message
    error_msg = std::format("In line {}, idx {}, token indicating end of line expected but is \"{}\"",  
        next_token.line(), next_token.idx(), next_token.value());

    return ParseResult::PARSE_FAIL;
}