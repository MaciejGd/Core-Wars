#pragma once
#include "ASTNode.h"
#include <memory>

class CExprParser {
public:
    CExprParser() = default;

    ParseResult EvaluateExpression(std::deque<Token>& tokens, int& result);

private:
    void m_TranslateToPostfix(std::deque<Token>& input, std::deque<Token>& postfix);

    int m_EvaluatePostifxExpression(std::deque<Token> &postfix);

    int m_PrecedenceHigher(Token& first_sign, Token& second_sign);

    ParseResult m_ParseArithmeticExpression(std::deque<Token>& tokens);

    ParseResult m_TraverseNodes(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes);
    
    int m_EvaluateArithmeticExpression(std::deque<Token>& tokens);

};