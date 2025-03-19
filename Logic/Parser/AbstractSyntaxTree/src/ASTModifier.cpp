#include "ASTModifier.h"

// Modifier GRAMMAR rule: 
// Modifier:=  mod | epsilon
// where: mod:= .a , .b, .ab, etc.


ParseResult CASTModifier::Eval(std::deque<Token>& tokens, std::stack<CASTNode*>& nodes)
{
    Token& token = tokens.front();
    if (token.type() == TokenType::MODIFIERS)
    {
        // modifier present in operation
        return ParseResult::PARSE_NEXT_TOKEN;
    }
    else 
    {
        // modifier is not present in operation
        return ParseResult::PARSE_OK;
    }
}