#include "ASTAddressMode.h"

// address mode is optional so do not throw error if it is not present
ParseResult CASTAddressMode::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes)
{
    Token next_token = tokens.front();
    if (next_token.type() == TokenType::ADDRESS_MODE)
    {
        tokens.pop_front();
        return ParseResult::PARSE_OK;
    }

}