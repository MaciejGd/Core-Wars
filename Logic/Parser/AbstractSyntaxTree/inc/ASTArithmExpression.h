#pragma once

#include "ASTNode.h"

/// @brief Class representing Arithmetic Expression node in Abstract Syntax Tree
/// 
/// Grammar rules for expressions are 
///
/// 1. ArithmExpression := Term 
/// 
/// 2. ArithmExpression := Term NewArithmExpression
///
/// Where NewArithmExpression is described as follows:
/// 
/// - NewArithmExpression:= ARITHM_OP NewArithmExpression
/// 
class CASTArithmExpression : public CASTNode {
public:
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) override;
};
    
    /// @brief Class representing NewArithmExpression node in Abstract Syntax Tree
    ///
    /// Introduced as fullfill to Expression node. CASTNewArithmExpression can be skipped, its
    /// grammar rule is like follow
    ///
    /// - NewArithmExpression := ARITHM_OP ArithmExpression |
    ///
class CASTArithmNewExpression : public CASTNode {
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) override;
};