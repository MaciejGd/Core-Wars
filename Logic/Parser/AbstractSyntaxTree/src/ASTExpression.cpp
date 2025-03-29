#include "ASTExpression.h"
#include "ASTTerm.h"
#include "ASTArithmExpression.h"
#include <string>

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
    // needed dummy CInstruction pointer to use Eval function 
    std::unique_ptr<CInstruction> dummy_instruction = nullptr; 
    if (top_node->Eval(tokens, nodes, dummy_instruction) == ParseResult::PARSE_FAIL)
    {
        return ParseResult::PARSE_FAIL;
    }

    return m_TraverseNodes(tokens, nodes);
}

int CASTExpression::m_PrecedenceHigher(Token& first_sign, Token& second_sign)
{
    std::string f_val = first_sign.value();
    std::string s_val = second_sign.value();
    if ((f_val == "+" || f_val == "-") && (s_val == "*" || s_val == "/"))
    {
        return 1; // resturn 1 when second_sign has higher precedence
    }
    return 0;
}

void CASTExpression::m_TranslateToPostfix(std::deque<Token>& input, std::deque<Token> &postfix)
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
}

int CASTExpression::m_EvaluatePostifxExpression(std::deque<Token> &postfix)
{
    std::stack<Token> numbers;
    while (!postfix.empty())
    {
        Token next_token = std::move(postfix.front());
        postfix.pop_front();
        if (next_token.type() == TokenType::NUMERICAL_VAL)
        {
            // if number spotted, simply push it to numbers stack
            numbers.push(next_token);
        }
        else if (next_token.type() == TokenType::ARITHM_OPS) 
        {
            std::string op = next_token.value();
            // we need to pop top token from stack and take its value as int 
            int pop_token = std::stoi(numbers.top().value()); 
            numbers.pop();
            // we take next token's value and transform it to int
            int top_token_value = std::stoi(numbers.top().value());
            if (op == "+")
            {
                numbers.top().SetValue(std::to_string(top_token_value + pop_token));
            }
            else if (op == "-")
            {
                numbers.top().SetValue(std::to_string(top_token_value - pop_token));
            }
            else if (op == "*")
            {
                numbers.top().SetValue(std::to_string(top_token_value * pop_token));
            }
            else if (op == "/")
            {
                numbers.top().SetValue(std::to_string(top_token_value / pop_token));
            }
        }
    }
    return std::stoi(numbers.top().value());
}

int CASTExpression::m_EvaluateArithmeticExpression(std::deque<Token>& tokens)
{   
    int line_of_occurence = tokens.front().line(); // for debug purposes
    // translate arithmetic expression to postfix Polish notation and evaluate
    std::deque<Token> postfix;
    m_TranslateToPostfix(tokens, postfix);
    int parameter_value = m_EvaluatePostifxExpression(postfix);
    LOG_WRN("In parsed file: {} in line: {} value evaluated from arithm expression is: {}", 
        CLexer::s_file_name, line_of_occurence, parameter_value);

    return parameter_value;
}


ParseResult CASTExpression::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction)
{
    // parse arithmetic expression
    std::deque<Token> arithmetic_tokens(tokens.begin(), tokens.end());
    if (m_ParseArithmeticExpression(arithmetic_tokens) == ParseResult::PARSE_FAIL)
    {
        // if parsing arithmetic expression failed, quit with exit error code
        return ParseResult::PARSE_FAIL;
    }

    // check how many tokens has been popped from queue of tokens
    int tokens_to_parse = tokens.size() - arithmetic_tokens.size();

    // create queue of tokens to be evaluated as arihtm expression by popping from original queue
    std::deque<Token> expression_tokens;
    for (int i = 0; i < tokens_to_parse; i++)
    {
        expression_tokens.push_back(tokens.front());
        tokens.pop_front();
    }

    int param_value = m_EvaluateArithmeticExpression(expression_tokens);
    // set value of the parameter in instruction
    instruction->CreateParamValue(param_value);

    return ParseResult::PARSE_OK;
}

