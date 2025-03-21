#include "ASTModifier.h"

// MODIFIER GRAMMAR RULE: 
// Modifier:=  mod | epsilon
// where mod:= .a , .b, .ab, etc.


ParseResult CASTModifier::Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes)
{
    Token& token = tokens.front();
    if (token.type() == TokenType::MODIFIERS)
    {
        // modifier present in operation, so pop it from the queue
        tokens.pop_front();
    }
    return ParseResult::PARSE_OK;
}