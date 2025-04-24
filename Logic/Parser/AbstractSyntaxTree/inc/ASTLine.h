#include "ASTNode.h"

/// Class representing line parsing node. First node to be evaluated for each line of tokens
class CASTLine : public IASTNode {
public:
    ParseResult Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<IASTNode>>& nodes, 
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) override;
};
