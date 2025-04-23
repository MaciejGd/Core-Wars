#include "ASTNode.h"


/// @brief Class representing modifier Node. Modifier is optional 
/// feature of every operation.
class CASTModifier : public IASTNode {
public:
    ParseResult Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<IASTNode>>& nodes, 
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) override; 
private:
    bool m_SetModifier(Token& token, std::unique_ptr<CInstruction>& instruction, std::string& error_msg);
};