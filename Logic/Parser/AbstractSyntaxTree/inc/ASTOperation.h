#include "ASTNode.h"


/// Class representing operation parsing node.
class CASTOperation : public IASTNode {
public:
    ParseResult Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<IASTNode>>& nodes, 
        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) override;

private:
    /// @brief Adds operation to instruction passed as param, basing on input token's value
    /// @param token token representing operation
    /// @param instruction instruction that we want to modify
    /// @return boolean indicating result of the operation
    bool m_SetOperation(Token& token, std::unique_ptr<CInstruction>& instruction, std::string& error_msg);
};