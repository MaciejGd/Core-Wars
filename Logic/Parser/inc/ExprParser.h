#pragma once
#include "ASTNode.h"
#include <memory>

/// Class responsible for parsing arithmetic expressions
class CExprParser {
public:
    CExprParser() = default;

    ParseResult EvaluateExpression(std::deque<Token>& tokens, int& result);

    /// @brief Get error message genarated during parsing
    /// @return error message in the form of string 
    inline const std::string GetErrorMessage() const { return m_error_msg; };
private:
    void m_TranslateToPostfix(std::deque<Token>& input, std::deque<Token>& postfix);

    int m_EvaluatePostifxExpression(std::deque<Token> &postfix);

    int m_PrecedenceHigher(Token& first_sign, Token& second_sign);

    ParseResult m_ParseArithmeticExpression(std::deque<Token>& tokens);

    ParseResult m_TraverseNodes(std::deque<Token>& tokens, std::stack<std::unique_ptr<IASTNode>>& nodes);
    
    int m_EvaluateArithmeticExpression(std::deque<Token>& tokens);

    // need to store error message 
    std::string m_error_msg;

};