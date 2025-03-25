#include "ASTExpression.h"
#include "ASTTerm.h"
#include "ASTArithmExpression.h"
#include <string>

int CASTExpression::m_PrecedenceHigher(Token& first_sign, Token& second_sign)
{
    std::string f_val = first_sign.value();
    std::string s_val = second_sign.value();
    if ((f_val == "+" || f_val == "-") && (s_val == "*" || s_val == "/"))
    {
        return 1; // resturn 1 when second_sign has higher precedence
    }
    else if ((s_val == "*" || s_val == "/") && (f_val == "*" ||   f_val == "/"))
    {
        // return 2 when first_sign precedence is equal to secod's sign precedendce
        return 2;
    }
    return 0;
}

ParseResult CASTExpression::m_ParseArithmeticExpression(std::deque<Token> &tokens)
{
    // we assume proper tokens has been already prepared for us
    // we need to create a stack of nodes
    std::stack<std::unique_ptr<CASTNode>> nodes;
    nodes.push(std::make_unique<CASTArithmExpression>());

    return m_TraverseNodes(tokens, nodes);
}

ParseResult CASTExpression::m_TraverseNodes(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes)
{
    // tokens arent necessarily empty after paring arithm op, in fact should be
    if (tokens.empty())
    {
        return ParseResult::PARSE_FAIL;
    }
    if (nodes.empty())
    {
        return ParseResult::PARSE_OK;
    } 
    //take top node from a stack and evaluate it 
    //LOG_WRN("In file {} | Stack size: {}", CLexer::s_file_name, nodes.size());
    std::unique_ptr<CASTNode> top_node = std::move(nodes.top());
    nodes.pop();
    //LOG_WRN("Top token to be parsed: {}", tokens.front().PrintFormat());
    if (top_node->Eval(tokens, nodes) == ParseResult::PARSE_FAIL)
    {
        return ParseResult::PARSE_FAIL;
    }

    return m_TraverseNodes(tokens, nodes);
}

int CASTExpression::m_EvaluateArithmeticExpression(std::deque<Token>& tokens)
{   
    std::deque<Token> postfix;
    m_TranslateToPostfix(tokens, postfix);

    return ParseResult::PARSE_OK;
}

bool CASTExpression::m_TranslateToPostfix(std::deque<Token>& input, std::deque<Token> &postfix)
{
    std::stack<Token> op;
    Token prev_token = input.front();
    // if first token indicates sign, add it to the value of next token immidiately
    if (prev_token.value() == "+" || prev_token.value() == "-")
    {
        input.pop_front();
        input.front().SetValue(prev_token.value() + input.front().value());
    }
    while (!input.empty())
    {
        Token actual_token = std::move(input.front());
        input.pop_front(); 
        if (actual_token.type() == TokenType::NUMERICAL_VAL)
        {
            postfix.push_back(actual_token);
        }
        else if (actual_token.type() == TokenType::ARITHM_OPS)
        {
            // if prev token not equal numerical value, then we analyze sign of the number
            if (prev_token.type() != NUMERICAL_VAL && prev_token.value() != ")")
            {
                // after parsing we are sure that only closing bracket and no numerical value preceeding
                // + or - means that we are analyzing sign of the number which should be instantly added to next token value
                std::string next_number = actual_token.value() + input.front().value();
                input.front().SetValue(next_number);
                continue;
            }
            // if operators stack is not empty and found precedence of operator is lower that stack's top  
            while (!op.empty() && op.top().value() != "(" && m_PrecedenceHigher(actual_token, op.top()) == 1)
            {   
                // pop from stack to the postfix queue
                postfix.push_back(op.top());
                op.pop();
            }
            op.push(actual_token);
        }
        else if (actual_token.value() == "(")
        {
            op.push(actual_token);
        }
        else if (actual_token.value() == ")")
        {
            // pop from op stack until opening bracket found            
            while (op.top().value() != "(")
            {
                postfix.push_back(op.top());
                op.pop();
            }
            // pop from stack remaining opening bracket
            op.pop(); 
        }
        prev_token = actual_token;
    }
    while (!op.empty())
    {
        postfix.push_back(op.top());
        op.pop();
    }
    // std::string reverse_polish_not_string = "";
    // for (const auto& x: postfix)
    // {
    //     reverse_polish_not_string += std::string(x.value());
    //     reverse_polish_not_string += " ";
    // }
    // LOG_WRN("Parameter in POLISH notation: {}", reverse_polish_not_string);
    return true;
}

ParseResult CASTExpression::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes)
{
    // parse arithmetic expression
    std::deque<Token> arithmetic_tokens(tokens.begin(), tokens.end());
    if (m_ParseArithmeticExpression(arithmetic_tokens) == ParseResult::PARSE_FAIL)
    {
        return ParseResult::PARSE_FAIL;
    }

    // check how many tokens has been popped from queue of tokens
    int tokens_to_parse = tokens.size() - arithmetic_tokens.size();

    // create queue of tokens to be evaluated as in arihtm expression by popping from original queue
    std::deque<Token> expression_tokens;
    for (int i = 0; i < tokens_to_parse; i++)
    {
        expression_tokens.push_back(tokens.front());
        tokens.pop_front();
    }

    int param_value = m_EvaluateArithmeticExpression(expression_tokens);

    return ParseResult::PARSE_OK;
}

