#include "ASTOperation.h"
#include "ASTModifier.h"


// OPERATION GRAMMAR RULE 
// Operation:= Op ModifierPrefix
// where Op:= dat, mov, add, etc.


ParseResult CASTOperation::Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes)
{
    // if token type is operation then parsing succeed and add CASTModifier to m_rhs
    Token &token = tokens.front();
    if (token.type() == TokenType::OPERATIONS) 
    {
        nodes.push(std::make_unique<CASTModifier>());
        tokens.pop_front();
        return ParseResult::PARSE_OK;
    }
    else 
    {
        LOG_ERR("Next token should be modifier, but its value is: {}", token.PrintFormat());
        return ParseResult::PARSE_FAIL;
    }
    
}