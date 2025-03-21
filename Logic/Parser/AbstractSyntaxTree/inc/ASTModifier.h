#include "ASTNode.h"


/// @brief Class representing modifier Node. Modifier is optional 
/// feature of every operation.
class CASTModifier : public CASTNode {
    ParseResult Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes) override; 
};