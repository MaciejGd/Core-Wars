#include "ASTExpression.h"
#include "ASTTerm.h"
#include "ASTArithmExpression.h"
#include <string>
#include "ExprParser.h"


ParseResult CASTExpression::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg)
{
    CExprParser expression_parser;
    int param = 0;
    if (expression_parser.EvaluateExpression(tokens, param) == ParseResult::PARSE_FAIL)
    {
        LOG_ERR("Failed to parse arithmetic expression");
        // get error message generated during parsing
        error_msg = expression_parser.GetErrorMessage();
        return ParseResult::PARSE_FAIL;
    }
    instruction->CreateParamValue(param);
    LOG_WRN("Front token after expression parsing: {}", tokens.front().value());
    return ParseResult::PARSE_OK;
}

