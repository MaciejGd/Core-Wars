#pragma once

#include "ASTNode.h"

/// Class representing arithmetic expressions parsing node.
class CASTArithmExpression : public IASTNode {
public:
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) override;
};
    
/// Class representing "arithm new expression" parsing node.
/// Introduced as fullfill to Expression node. CASTNewArithmExpression can be skipped, its
/// grammar rule is like follow
/// - NewArithmExpression := ARITHM_OP ArithmExpression |
class CASTArithmNewExpression : public IASTNode {
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) override;
};