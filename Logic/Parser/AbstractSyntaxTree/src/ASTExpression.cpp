#include "ASTExpression.h"
#include "ASTTerm.h"

// grammar rule for CASTExpression
// EXPRESSION := TERM NEWEXPRESSION


int CASTExpression::m_PrecedenceHigher(Token& first_sign, Token& second_sign)
{
    if ((first_sign.value() == "+" || first_sign.value() == "-") 
        && (second_sign.value() == "*" ||   second_sign.value() == "/"))
    {
        return 1; // resturn 1 when second_sign has higher precedence
    }
    else if ((second_sign.value() == "+" || second_sign.value() == "-") 
        && (first_sign.value() == "*" ||   first_sign.value() == "/"))
    {
        return 2; // return 2 when first_sign has higher precedence
    }
    return 0;
}

ParseResult CASTExpression::m_ParseArithmeticExpression(std::deque<Token> &tokens, 
    std::stack<std::unique_ptr<CASTNode>> &nodes, std::deque<Token> &output_tokens)
{
    return ParseResult();
}

ParseResult CASTExpression::m_EvaluateParameter(std::deque<Token>& tokens, int& result)
{
    std::stack<Token> expr;
    std::deque<Token> postfix;
    Token actual_token = std::move(tokens.front());
    tokens.pop_front();
    TokenType prev_type;
    // validate first token
    if (actual_token.type() == TokenType::NUMERICAL_VAL)
    {
        postfix.push_back(actual_token);
    }
    if (actual_token.value() == "(" || actual_token.value() == "+" ||
        actual_token.value() == "-")
    {
        expr.push(actual_token);
    }
    else {
        return ParseResult::PARSE_FAIL;
    }

    prev_token = actual_token;

    bool should_run = true;
    int open_brackets = 0;
    while (should_run)
    {
        actual_token = std::move(tokens.front());
        tokens.pop_front(); 
        if (actual_token.type() == TokenType::NUMERICAL_VAL)
        {
            // cant have to nums next to each other without operator between them
            if (prev_token.type() == TokenType::NUMERICAL_VAL)
            {
                return ParseResult::PARSE_FAIL;
            }
        }
        else if (actual_token.type() == TokenType::ARITHM_OPS)
        {
;
        }
        else if (actual_token.type() == TokenType::SEPARATOR)
        {
;
        }
        if (expr.top().value() == "(" )
        {
;
        }
    }

    return ParseResult::PARSE_OK;
}


ParseResult CASTExpression::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes)
{
    nodes.push(std::make_unique<CASTNewExpression>());
    nodes.push(std::make_unique<CASTTerm>());
    return ParseResult::PARSE_OK;
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
