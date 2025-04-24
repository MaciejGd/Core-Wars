#pragma once

#include "ASTNode.h"

/// Class representing end line parsing node. Every line of tokens should end with this node
class CASTEndLine : public IASTNode {
public:
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) override;
};