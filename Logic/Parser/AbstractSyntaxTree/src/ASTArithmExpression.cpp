#include "ASTArithmExpression.h"
#include "ASTTerm.h"

// GRAMMAR RULE for arithm expression
// ARITHMEXPRESSION := TERM ARITHMNEWEXPRESSION

ParseResult CASTArithmExpression::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg)
{
    nodes.push(std::make_unique<CASTArithmNewExpression>());
    nodes.push(std::make_unique<CASTTerm>());
    return ParseResult::PARSE_OK;
}

// grammar rule for CASTNewExpression
// NEWEXPRESSION := ARITHM_OPERATOR TERM NEWEXPRESSION | nothing
// I wont create separate node for arithm operator but rather check 
// next token for being arithm op in NewExpression itself
ParseResult CASTArithmNewExpression::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg)
{
    Token& next_token = tokens.front();
    if (next_token.type() == TokenType::ARITHM_OPS) 
    {
        tokens.pop_front();
        nodes.push(std::make_unique<CASTArithmExpression>());
    }
    return ParseResult::PARSE_OK;
}
