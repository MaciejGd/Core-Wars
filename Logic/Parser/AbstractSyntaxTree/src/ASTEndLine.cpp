#include "ASTEndLine.h"

ParseResult CASTEndLine::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction)
{
    Token& next_token = tokens.front();
    tokens.pop_front();
    if (next_token.type() == TokenType::END_LINE)
    {
        return ParseResult::PARSE_OK;
    }
    PARSING_FAIL(CLexer::s_file_name, next_token);
    LOG_ERR("EndLine token expected but present token is {}", next_token.PrintFormat());
    return ParseResult::PARSE_FAIL;
}