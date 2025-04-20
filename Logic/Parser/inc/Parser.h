#pragma once

#include "Lexer.h"
#include "ASTNode.h"
#include "Instruction.h"

#include <vector>
#include <map>

/// @brief Class checking if grammar rules of RedCode language 
///
/// has been met. Analyze tokens retrieved during the process of lexical
///
/// analysis and builts initial instructions for a player based on that.
class CParser {
public:
    /// @brief Function responsible for parsing input RedCode program and building initial instructions based on that
    /// @param tokens 2D vector of tokens, retrieved during lexing stage
    /// @param instructions vector of instructions, to be filled with parsed instructions
    /// @param offset offset to program counter from the first instruction
    /// @return boolean value indicating result of parsing a file
    bool ParseFile(TokenContainer& tokens, std::vector<std::unique_ptr<CInstruction>>& instructions, int& offset);

    /// @brief Get error message genrated during parsing
    /// @return error message
    inline const std::string GetErrorMessage() const { return m_error_msg; };
private:
    /// @brief Parse one row of tokens
    /// @param tokens_row vector of Tokens to be parsed
    /// @param instructions unique_ptr of CInstruction, to be modified during parsing of the line
    /// @return boolean indicating result of parsing a line
    bool m_ParseLine(const std::vector<Token>& tokens_row, std::unique_ptr<CInstruction>& instruction);

    /// @brief Gether label tags of lines
    /// @param tokens container of tokens to be analyzed
    /// @return boolean indicating success of operation
    bool m_GatherLabels(TokenContainer& tokens);

    /// @brief Removes labels and place relative numbers in its place
    /// @param tokens two dimensional array of tokens
    /// @return bool indicating status of removing labels operation
    bool m_RemoveLabels(TokenContainer& tokens);

    /// @brief Switch labels in token container to proper values
    /// @param tokens container of tokens to be analyzed
    /// @return boolean indicating success of switching labels
    bool m_SwitchLabelsInFile(TokenContainer& tokens);

    /// @brief Function for switching labels to associated expressions
    /// @param tokens stl container of Tokens to be analyzed
    /// @param line_idx index of analyzed line
    /// @return boolean indicating result of switching operation 
    template<template<typename T> class Container>
    bool m_SwitchLabels(Container<Token>& tokens, int line_idx);

    /// @brief Analyze pseudo instructions END, ORG, EQU separately 
    /// @param tokens container with lexed tokens
    /// @return bool indicating status of analyzing pseudo instructions operations
    bool m_AnalyzePseudoInstructions(TokenContainer& tokens);

    /// @brief Parse arithmetic expression to count index of starting operation for the player
    /// @return offset of first operation executed in relation to first operation of parsed code
    int m_EvaluateStartIndex();

    /// @brief Recursive function for traversing Abstract Syntax Tree
    /// @param tokens queue of tokens to be parsed
    /// @param nodes stack that next nodes will be pushed to
    /// @param instruction pointer to instruction to be modified during parsing line
    /// @return boolean indicating result of the parsing
    bool m_TraverseAST(std::deque<Token>& tokens, std::stack<std::unique_ptr<CASTNode>>& nodes,
                        std::unique_ptr<CInstruction>& instruction);


    /// @brief Clear or containers of CParser object
    void m_ClearContainers();

    /// @brief replace label tag of the line with value declared with EQU pseudo operation
    bool m_ReplaceLineTagWithEqu();
    
    // map we will store label values to be switched with EQU label
    std::map<std::string, std::vector<Token>> m_equ_map;

    // we need to store vector of tokens in case whole expression need to be evaluated 
    std::deque<Token> m_prog_start;

    // map for storing labels with line of their occurence
    std::map<std::string, int> m_labels;

    std::string m_error_msg;

};


// Need to implement this function as template as I would like to handle switching labels
// in deques and vectors in the same manner  
template<template<typename T> class Container>
bool CParser::m_SwitchLabels(Container<Token>& tokens, int line_idx)
{
    for (int j = 0; j < tokens.size(); j++)
    {
        Token& curr = tokens[j];
        if (curr.type() != TokenType::LABEL)
        {
            continue;
        }
        // check if label was defined with EQU pseudo operation
        if (m_equ_map.find(curr.value()) != m_equ_map.end())
        {
            // insert equ expression in the place of label
            Container<Token> result(tokens.begin(), tokens.begin() + j);
            // we want to skip last token as it is end line token
            Container<Token> postfix(tokens.begin() + j + 1, tokens.end());
            std::copy(m_equ_map[curr.value()].begin(), m_equ_map[curr.value()].end(), std::back_inserter(result));
            std::move(postfix.begin(), postfix.end(), std::back_inserter(result));
            tokens = std::move(result);
            // we want to analyze token at i again as it can be label, so need to decrease i
            j--;
            continue;
        }
        // if used label not declared nad not used in EQU, return false
        if (m_labels.find(curr.value()) == m_labels.end())
        {
            LOG_ERR("In line {}, idx {}, using label: {} that has not been previously declared",
                curr.line(), curr.idx(), curr.value());
            return false;
        }

        int label_declaration_idx = m_labels[curr.value()];
                    
        std::string label_switch_val = std::to_string(label_declaration_idx - line_idx);
        // change value and type of the token
        curr.SetValue(label_switch_val);
        curr.SetType(TokenType::NUMERICAL_VAL);
        //LOG_WRN("Switched to value {}", curr.value());
        LOG_DBG("Successfully switched label with numerical value in line {}, idx {}", 
            curr.line(), curr.idx());

    }
    return true;
}