#include "ASTNode.h"


/// @brief Class representing Operation node in Abstract Syntax Tree
/// 
/// Grammar rule for operation is 
///
/// - Operation := OperationToken Modifier
/// 
/// where OperationToken is one of the operations, ex. mov, add, equ, etc.
class CASTOperation : public CASTNode {
    ParseResult Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes) override;
};