#include "ASTNode.h"


class CASTLine : public CASTNode {
public:
    ParseResult Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes, 
                        std::unique_ptr<CInstruction>& instruction) override;
};
