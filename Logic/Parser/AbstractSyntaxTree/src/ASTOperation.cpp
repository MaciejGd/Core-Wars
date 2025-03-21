#include "ASTOperation.h"
#include "ASTModifier.h"


// OPERATION GRAMMAR RULE 
// Operation:= Op ModifierPrefix
// where Op:= dat, mov, add, etc.


ParseResult CASTOperation::Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes)
{
    // if token type is operation then parsing succeed and add CASTModifier to m_rhs
    Token& next_token = tokens.front();
    tokens.pop_front();
    // if type of next token is not operation, then parsing shoul fail
    if (next_token.type() != TokenType::OPERATIONS) 
    {
        LOG_ERR("Error in file {} line: {}, idx: {}, ", 
            Lexer::s_file_name, next_token.line(), next_token.idx());
        LOG_ERR("Line should start with operator but starts with token => {}", next_token.PrintFormat());
        return ParseResult::PARSE_FAIL;
    }
    // if operation token successfully parsed, push modifier to stack
    nodes.push(std::make_unique<CASTModifier>());
    return ParseResult::PARSE_OK;

}