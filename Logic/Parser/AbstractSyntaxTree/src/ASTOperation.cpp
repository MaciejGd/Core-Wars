#include "ASTOperation.h"
#include "ASTModifier.h"

// operation includes
#include "Operation.h"
#include "OperationDAT.h"
#include "OperationMOV.h"
#include "OperationADD.h"
#include "OperationSUB.h"
#include "OperationMUL.h"
#include "OperationDIV.h"
#include "OperationMOD.h"
#include "OperationJMP.h"
#include "OperationJMZ.h"
#include "OperationJMN.h"
#include "OperationDJN.h"
#include "OperationSPL.h"
#include "OperationCMP.h"
#include "OperationSLT.h"
#include "OperationORG.h"
#include "OperationEQU.h"
#include "OperationEND.h"



ParseResult CASTOperation::Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes, 
    std::unique_ptr<CInstruction>& instruction, std::string& error_msg)
{
    // if token type is operation then parsing succeed and add CASTModifier to m_rhs
    Token& next_token = tokens.front();
    tokens.pop_front();
    // if type of next token is not operation, then parsing shoul fail
    if (next_token.type() != TokenType::OPERATIONS) 
    {
        PARSING_FAIL(CLexer::s_file_name, next_token);
        LOG_ERR("Line should start with operator but starts with token => {}", next_token.PrintFormat());
        error_msg = std::format("In line {}, idx {}, operator expected, got \"{}\"",  
            next_token.line(), next_token.idx(), next_token.value());
        return ParseResult::PARSE_FAIL;
    }
    // if operation token successfully parsed, push modifier to stack
    if (m_SetOperation(next_token, instruction, error_msg) == false)
    {
        return ParseResult::PARSE_FAIL;
    }
    nodes.push(std::make_unique<CASTModifier>());
    return ParseResult::PARSE_OK;
}

bool CASTOperation::m_SetOperation(Token &token, std::unique_ptr<CInstruction> &instruction, std::string& error_msg)
{
    std::string op_string = token.value();

    if (op_string == "dat") 
    {
        instruction->SetOperation(std::make_unique<COperationDAT>());
    }
    else if (op_string == "mov") 
    {
        instruction->SetOperation(std::make_unique<COperationMOV>());
    }
    else if (op_string == "add") 
    {
        instruction->SetOperation(std::make_unique<COperationADD>());
    }
    else if (op_string == "sub") 
    {
        instruction->SetOperation(std::make_unique<COperationSUB>());
    }
    else if (op_string == "mul") 
    {
        instruction->SetOperation(std::make_unique<COperationMUL>());
    }
    else if (op_string == "div") 
    {
        instruction->SetOperation(std::make_unique<COperationDIV>());
    }
    else if (op_string == "mod") 
    {
        instruction->SetOperation(std::make_unique<COperationMOD>());
    }
    else if (op_string == "jmp") 
    {
        instruction->SetOperation(std::make_unique<COperationJMP>());
    }
    else if (op_string == "jmz") 
    {
        instruction->SetOperation(std::make_unique<COperationJMZ>());
    }
    else if (op_string == "jmn") 
    {
        instruction->SetOperation(std::make_unique<COperationJMN>());
    }
    else if (op_string == "djn") 
    {
        instruction->SetOperation(std::make_unique<COperationDJN>());
    }
    else if (op_string == "spl") 
    {
        instruction->SetOperation(std::make_unique<COperationSPL>());
    }
    else if (op_string == "cmp") 
    {
        instruction->SetOperation(std::make_unique<COperationCMP>());
    }
    else if (op_string == "seq") 
    {
        instruction->SetOperation(std::make_unique<COperationSLT>());
    }
    else if (op_string == "org") 
    {
        instruction->SetOperation(std::make_unique<COperationORG>());
    }
    else if (op_string == "equ") 
    {
        instruction->SetOperation(std::make_unique<COperationEQU>());
    }
    else if (op_string == "end") 
    {
        instruction->SetOperation(std::make_unique<COperationEND>());
    }
    else 
    {
        PARSING_FAIL(CLexer::s_file_name, token);
        LOG_ERR("Instruction not recognized");
        error_msg = std::format("In line {}, idx {}, operation \"{}\" NOT recognized.",  
            token.line(), token.idx(), token.value());
        return false;
    }
    return true;
}
