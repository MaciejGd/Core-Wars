#include "ASTAdressMode.h"

// address mode is optional so do not throw error if it is not present
ParseResult CASTAdressMode::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes)
{
    Token next_token = tokens.front();
    if (next_token.type() == TokenType::ADDRESS_MODE)
    {
        tokens.pop();
    }
    return ParseResult::PARSE_OK;
}