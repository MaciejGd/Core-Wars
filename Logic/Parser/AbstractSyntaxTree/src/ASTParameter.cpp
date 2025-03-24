#include "ASTParameter.h"
#include "ASTAddressMode.h"
#include "ASTExpression.h"

// parameter to operation can be
// PARAM := adressmode expression

ParseResult CASTParameter::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes)
{
    nodes.push(std::make_unique<CASTExpression>());
    nodes.push(std::make_unique<CASTAddressMode>());
    return ParseResult::PARSE_OK;
}


