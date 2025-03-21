#include "ASTLine.h"

// MODIFIER GRAMMAR RULE: 
// Modifier:= operation param1 coma param2
// modifier can start with label however it got removed 
// before so we do not need to care about that

ParseResult CASTLine::Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes) 
{
    // push to stack of nodes below grammar rule:
    // Line := operation param coma param
    nodes.push(std::make_unique<CASTParameter>());
    nodes.push(std::make_unique<CASTComa>());
    nodes.push(std::make_unique<CASTParameter>());
    nodes.push(std::make_unique<CASTOperation>());
    return ParseResult::PARSE_OK;
    
}
