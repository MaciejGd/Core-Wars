#pragma once

#include "ASTNode.h"


class CASTTerm : public CASTNode {
public:
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes);    
};