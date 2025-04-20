#include "ASTTerm.h"

#include "ASTClosingBracket.h"
#include "ASTNumber.h"
#include "ASTArithmExpression.h"

ParseResult CASTTerm::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg)
{
    Token next_token = tokens.front();
    // number can be signed, so we need to check if + or - is present
    tokens.pop_front();
    if (next_token.type() == TokenType::LABEL)
    {
        // wont be needed in a future when labels will be removed
        return ParseResult::PARSE_OK;
    }
    if (next_token.type() == TokenType::NUMERICAL_VAL)
    {
        return ParseResult::PARSE_OK;
    }
    else if (next_token.value() == "(")
    {
        nodes.push(std::make_unique<CASTClosingBracket>());
        nodes.push(std::make_unique<CASTArithmExpression>());
        return ParseResult::PARSE_OK;
    }
    else if (next_token.value() == "+" || next_token.value() == "-")
    {
        nodes.push(std::make_unique<CASTNumber>());
        return ParseResult::PARSE_OK;
    }
    PARSING_FAIL(CLexer::s_file_name, next_token);
    LOG_ERR("Token should be either label, number or opening bracket but is {}", next_token.PrintFormat());
    error_msg = std::format("In line {}, idx {}, either label, number or opening bracket expected, got \"{}\"",  
        next_token.line(), next_token.idx(), next_token.value());
    return ParseResult::PARSE_FAIL;
}