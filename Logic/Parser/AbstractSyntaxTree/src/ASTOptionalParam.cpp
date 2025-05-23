#include "ASTOptionalParam.h"
#include "ASTParameter.h"
#include "ASTEndLine.h"

ParseResult CASTOptionalParam::Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
                        std::unique_ptr<CInstruction>& instruction, std::string& error_msg)
{
    Token& next_token = tokens.front();
    tokens.pop_front();
    if (next_token.type() == TokenType::END_LINE) 
    {
        // we return ok status as second parameter is optional
        return ParseResult::PARSE_OK;
    }
    else if (next_token.value() == ",")
    {
        // coma spotted means that second parameter should be parsed
        nodes.push(std::make_unique<CASTEndLine>());
        nodes.push(std::make_unique<CASTParameter>());
        return ParseResult::PARSE_OK;
    }
    PARSING_FAIL(CLexer::s_file_name, next_token);
    LOG_ERR("Line should end in here, or coma indicating second parameter should be passed" );
    error_msg = std::format("In line {}, idx {}, either \",\" or \"EndLine\" expected, got \"{}\"",  
        next_token.line(), next_token.idx(), next_token.value());
    return ParseResult::PARSE_FAIL;
}