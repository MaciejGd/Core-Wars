#include "ASTLine.h"

// MODIFIER GRAMMAR RULE: 
// Modifier:=  label operation param1 coma param2
// where mod:= .a , .b, .ab, etc.


ParseResult CASTLine::Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes) 
{
    
}
