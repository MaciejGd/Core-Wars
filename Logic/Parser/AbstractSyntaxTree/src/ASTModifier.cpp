#include "ASTModifier.h"

// MODIFIER GRAMMAR RULE: 
// Modifier:=  mod | epsilon
// where mod:= .a , .b, .ab, etc.


ParseResult CASTModifier::Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes, 
    std::unique_ptr<CInstruction>& instruction)
{
    Token& next_token = tokens.front();
    if (next_token.type() != TokenType::MODIFIERS)
    {
        // modifier present not present so set as defaults
        instruction->SetModifier(ModifierType::DEFAULT);
        return ParseResult::PARSE_OK;    
    }
    // modifier found
    tokens.pop_front();
    if (m_SetModifier(next_token, instruction) == false)
    {
        return ParseResult::PARSE_FAIL;
    }
    return ParseResult::PARSE_OK;    
}

bool CASTModifier::m_SetModifier(Token &token, std::unique_ptr<CInstruction> &instruction)
{
    std::string modifier = token.value();
    LOG_ERR("Modifier value: {}", modifier)
    if (modifier == ".a")
    {
        instruction->SetModifier(ModifierType::A);
    }
    else if (modifier == ".b")
    {
        instruction->SetModifier(ModifierType::B);
    }
    else if (modifier == ".ab")
    {
        instruction->SetModifier(ModifierType::AB);
    }
    else if (modifier == ".ba")
    {
        instruction->SetModifier(ModifierType::BA);
    }
    else if (modifier == ".f")
    {
        instruction->SetModifier(ModifierType::F);
    }
    else if (modifier == ".i")
    {
        instruction->SetModifier(ModifierType::I);
    }
    else if (modifier == ".x")
    {
        instruction->SetModifier(ModifierType::X);
    }
    else 
    {
        PARSING_FAIL(CLexer::s_file_name, token);
        LOG_ERR("Modifier value has not been recognized");
        return false;
    }
    return true;
}
