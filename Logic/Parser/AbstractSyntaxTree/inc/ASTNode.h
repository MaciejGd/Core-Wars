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


/// Interface for all parsing nodes
class IASTNode {
public:
    /// @brief Evaluate parsing node
    /// @param tokens deque of tokens to be analyzed during parsing
    /// @param nodes stack of nodes, push nodes got during evaluation of current node to stack
    /// @param instruction instruction built during process of parsing
    /// @param error_msg error message generated during parsing node
    /// @return ParseResult enumeration type indicating if parsing succeeded or failed
    virtual ParseResult Eval(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
        std::unique_ptr<CInstruction>& instruction, std::string& error_msg) = 0;
};