#pragma once

#include "Token.h"
#include "logger.h"

#include <vector>
#include <memory>
#include <deque> // for token queue
#include <stack>

// parsing return codes
enum ParseResult {
    PARSE_END,
    PARSE_OK, // tells parser that Node has been parsed proprly (token SHALL NOT be removed)
    PARSE_NEXT_TOKEN, // tells parser to skip current token, as it is valid
    PARSE_FAIL // indicates unproper Node during the parsing
};


// evaluation of node
class CASTNode {
public:
    virtual ParseResult Eval(std::deque<Token>& token, std::stack<CASTNode*>& nodes) = 0;
};