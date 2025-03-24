#pragma once

#include "logger.h"
#include "Lexer.h" // we need to know Token class def and name of the file
// currently analyzed

#include <vector>
#include <memory>
#include <deque> // for token queue
#include <stack>


#define PARSING_FAIL(file_name, failing_token) \
    LOG_ERR("Error in parsing file {} line: {}, idx: {}, ", \
        file_name, failing_token.line(), failing_token.idx());\

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
    virtual ParseResult Eval(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes) = 0;
};