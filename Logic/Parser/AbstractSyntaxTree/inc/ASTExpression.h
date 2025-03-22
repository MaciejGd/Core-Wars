#pragma once

#include "ASTNode.h"

/// @brief Class representing Expression node in Abstract Syntax Tree
/// 
/// Grammar rules for expressions are 
///
/// 1. Expression := Term 
/// 
/// 2. Expression := Term NewExpression
///
/// Where NewExpression is described as follows:
/// 
/// - NewExpression:= ARITHM_OP Expression
/// 
class CASTExpression : public CASTNode {
public:
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes) override;
};

/// @brief Class representing NewExpression node in Abstract Syntax Tree
///
/// Introduced as fullfill to Expression node. CASTNewExpression can be skipped, its
/// grammar rule is like follow
///
/// - NewExpression := ARITHM_OP Expression |
///
class CASTNewExpression : public CASTNode {
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes) override;
};