#pragma once

// we need to set rules for parsing 
// eval should return return codes 


enum ParseResult {
    PARSE_END,
    PARSE_OK,
    PARSE_FAIL
};


// grammar rules:  (ε is used for epsilo)
// Program = Line + newLine  # at least one line of code is needed
// newLine = (line + NewLine) | ε // main abstract grammar in the redcode code
// line = label + operation + param + separator + param
// line = operation + param + separator + param
// 
// operation = operation(TOKEN_TYPE::OPERATION);
// operation = operation + modifier


// evaluation of node
class ASTNode {
public:
    ASTNode(){};
    virtual void Eval() = 0;
private:
};