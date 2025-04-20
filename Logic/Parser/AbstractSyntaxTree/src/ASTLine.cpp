#include "ASTLine.h"
#include "ASTParameter.h"
#include "ASTOperation.h"
#include "ASTOptionalParam.h"

// MODIFIER GRAMMAR RULE: 
// Modifier:= operation param optionalParam
// where field is optional
// modifier can start with label however it got removed 
// before so we do not need to care about that

ParseResult CASTLine::Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes, 
    std::unique_ptr<CInstruction>& instruction, std::string& error_msg)
{
    nodes.push(std::make_unique<CASTOptionalParam>());
    nodes.push(std::make_unique<CASTParameter>());
    nodes.push(std::make_unique<CASTOperation>());
    return ParseResult::PARSE_OK;
}
