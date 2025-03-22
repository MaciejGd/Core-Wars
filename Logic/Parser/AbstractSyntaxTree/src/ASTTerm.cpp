#include "ASTTerm.h"

#include "ASTClosingBracket.h"
#include "ASTNumber.h"
#include "ASTExpression.h"

ParseResult CASTTerm::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes)
{
    Token next_token = tokens.front();
    // number can be signed, so we need to check if + or - is present
    tokens.pop_front();
    if (next_token.type() == TokenType::LABEL)
    {
        return ParseResult::PARSE_OK;
    }
    else if (next_token.type() == TokenType::NUMERICAL_VAL)
    {
        return ParseResult::PARSE_OK;
    }
    else if (next_token.value() == "(")
    {
        nodes.push(std::make_unique<CASTClosingBracket>());
        nodes.push(std::make_unique<CASTExpression>());
        return ParseResult::PARSE_OK;
    }
    else if (next_token.value() == "+" || next_token.value() == "-")
    {
        nodes.push(std::make_unique<CASTNumber>());
        return ParseResult::PARSE_OK;
    }
    LOG_ERR("Error in parsign file {}, in line {}, idx {}", Lexer::s_file_name, next_token.line(), next_token.idx());
    LOG_ERR("Token should be either label, number or opening bracket but is {}", next_token.PrintFormat());
    return ParseResult::PARSE_FAIL;
}