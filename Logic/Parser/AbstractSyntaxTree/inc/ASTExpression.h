#pragma once

#include "ASTNode.h"

/// Class representing expression parsing node.
class CASTExpression : public IASTNode {    
public:
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) override;
};