#pragma once

#include "ASTNode.h"
#include "Instruction.h"

class CASTAddressMode : public CASTNode {
public:
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction) override;

private:
    void m_AddAddressMode(Token& token, std::unique_ptr<CInstruction>& instruction);
};