#pragma once

#include "ASTNode.h"

class CASTExpression : public CASTNode {
public:
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes);
};

class CASTNewExpression : public CASTNode {
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes);
};