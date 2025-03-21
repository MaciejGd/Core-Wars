#include "ASTNode.h"


class CASTLine : public CASTNode {
public:
    ParseResult Eval(std::deque<Token>& token, sted::stack<std::unique_ptr<CASTNode>>& nodes) override;
};