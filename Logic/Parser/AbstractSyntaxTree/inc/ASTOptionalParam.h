#pragma once


#include "ASTNode.h"

class CASTOptionalParam : public CASTNode {
public:
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction) override;
};