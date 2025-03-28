#pragma once

#include "ASTNode.h"


class CASTExpression : public CASTNode {
private:
    
    ParseResult m_ParseArithmeticExpression(std::deque<Token>& tokens);

    ParseResult m_TraverseNodes(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes);
    
    int m_EvaluateArithmeticExpression(std::deque<Token>& tokens);

    /// @brief Function to translate arithmetic expression from infix to postfix
    /// @param input input queue of tokens to be translated
    /// @param postfix tokens translated to postfix notation
    /// @return 
    bool m_TranslateToPostfix(std::deque<Token>& input, std::deque<Token>& postfix);
    int m_EvaluatePostifxExpression(std::deque<Token> &postfix);

    int m_PrecedenceHigher(Token& first_sign, Token& second_sign);
public:
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction) override;
};