#pragma once

#include "ASTNode.h"
#include "Instruction.h"

class CASTAddressMode : public IASTNode {
public:
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) override;

private:
    void m_SetAddressMode(Token& token, std::unique_ptr<CInstruction>& instruction);
};