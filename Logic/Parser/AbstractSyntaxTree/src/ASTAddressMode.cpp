#include "ASTAddressMode.h"
#include "ParameterDirect.h"
#include "ParameterImmidiate.h"
#include "ParameterIndirect.h"
#include "ParameterPostInc.h"
#include "ParameterPreDecr.h"

// address mode is optional so do not throw error if it is not present
ParseResult CASTAddressMode::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction)
{
    Token next_token = tokens.front();
    if (next_token.type() == TokenType::ADDRESS_MODE)
    {
        tokens.pop_front();
    }
    // add proper address mode and add it to instruction
    m_SetAddressMode(next_token, instruction);
    return ParseResult::PARSE_OK;
}

// function for choosing appropriate address mode and adding it to instruction
void CASTAddressMode::m_SetAddressMode(Token &token, std::unique_ptr<CInstruction> &instruction)
{
    std::string modifier = token.value();
    std::string log_param_type; 
    if (modifier == "#")
    {
        log_param_type = "immidiate";
        instruction->CreateParameter(std::make_unique<CParameterImmidiate>());
    }
    else if (modifier == "@")
    {
        log_param_type = "indirect";
        instruction->CreateParameter(std::make_unique<CParameterIndirect>());
    }
    else if (modifier == "<")
    {
        log_param_type = "predecrement";
        instruction->CreateParameter(std::make_unique<CParameterPreDecr>());
    }
    else if (modifier == ">")
    {
        log_param_type = "postincrement";
        instruction->CreateParameter(std::make_unique<CParameterPostInc>());
    }
    else 
    {
        log_param_type = "direct";
        instruction->CreateParameter(std::make_unique<CParameterDirect>());
    }
    LOG_WRN("In file {} line: {}, set parameter type as {}", CLexer::s_file_name, 
            token.line(), log_param_type);
}

