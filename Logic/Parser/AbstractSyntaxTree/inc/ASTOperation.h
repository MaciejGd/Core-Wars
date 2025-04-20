#include "ASTNode.h"


/// @brief Class representing Operation node in Abstract Syntax Tree
/// 
/// Grammar rule for operation is 
///
/// - Operation := OperationToken Modifier
/// 
/// where OperationToken is one of the operations, ex. mov, add, equ, etc.
class CASTOperation : public CASTNode {
public:
    ParseResult Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes, 
        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) override;

private:
    /// @brief Adds operation to instruction passed as param, basing on input token's value
    /// @param token token representing operation
    /// @param instruction instruction that we want to modify
    /// @return boolean indicating result of the operation
    bool m_SetOperation(Token& token, std::unique_ptr<CInstruction>& instruction, std::string& error_msg);
};