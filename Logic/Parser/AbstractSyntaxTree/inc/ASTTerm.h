#pragma once

#include "ASTNode.h"


/// @brief Class for representing Term Abstrax Syntax Tree node
/// grammar rules for CASTTerm are:
///
/// 1. Term := number
///
/// 2. Term := Label
///
/// 3. Term := ( Expression )
///
class CASTTerm : public IASTNode {
public:
    ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) override;    
};