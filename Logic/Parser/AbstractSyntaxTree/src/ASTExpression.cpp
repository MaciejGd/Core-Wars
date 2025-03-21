#include "ASTExpression.h"

// grammar rule for CASTExpression
// EXPRESSION := TERM NEWEXPRESSION

ParseResult CASTExpression::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes)
{
    nodes.push(std::make_unique<CASTNewExpression>());
    nodes.push(std::make_unique<CASTTerm>());
}

// grammar rule for CASTNewExpression
// NEWEXPRESSION := ARITHM_OPERATOR TERM NEWEXPRESSION | nothing
// I wont create separate node for arithm operator but rather check 
// next token for being arithm op in NewExpressionw
ParseResult CASTNewExpression::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes)
{
    Token& next_token = tokens.front();
    if (next_token.type() == TokenType::ARITHM_OPS) 
    {
        tokens.pop_front();
        nodes.push(std::make_unique<CASTExpression>());
    }
    return ParseResult::PARSE_OK;
}
