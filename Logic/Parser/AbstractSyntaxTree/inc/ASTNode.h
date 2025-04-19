#pragma once

#include "logger.h"
#include "Lexer.h" // we need to know Token class def and name of the file
#include "Instruction.h"
// currently analyzed

#include <vector>
#include <memory>
#include <deque> // for token queue
#include <stack>


#define PARSING_FAIL(file_name, failing_token) \
    LOG_ERR("Error in parsing file {} line: {}, idx: {}, ", \
        file_name, failing_token.line(), failing_token.idx());\

/// Parsing return codes, possible values:
/// - PARSE_FAIL: failed to parse
/// - PARSE_OK:   succeed to parse
enum ParseResult {
    PARSE_FAIL,  // indicates unproper Node during the parsing
    PARSE_OK     // tells parser that Node has been parsed proprly (token SHALL NOT be removed)
};


// evaluation of node
class CASTNode {
public:
    virtual ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
        std::unique_ptr<CInstruction>& instruction) = 0;
};