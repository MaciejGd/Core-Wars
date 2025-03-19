#include "ASTNode.h"


/// @brief Class for representing Node responsible of handling 
/// operation (ex. mov, jmp). 
class CASTOperation : public CASTNode {
    ParseResult Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes);
};