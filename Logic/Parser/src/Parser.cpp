#include "Parser.h"

#include "logger.h"
#include "ASTLine.h"

#include <string>
#include <unordered_map>
#include <stack>
#include <deque>

bool CParser::ParseFile(TokenContainer &tokens, std::vector<std::unique_ptr<CInstruction>>& instructions)
{
     // remove labels from the line starts perform some initial checking
    if (!m_RemoveLabels(tokens))
    {
        return false;
    }
    for (int i = 0; i < tokens.size(); i++) 
    {
        instructions.push_back(std::make_unique<CInstruction>());
        if (!m_ParseLine(tokens[i], instructions.back()))
        {
            LOG_ERR("Error in parsing, quiting execution");        
            return false;
        }
    }
    return true;
}

bool CParser::m_ParseLine(const std::vector<Token> &tokens_row, std::unique_ptr<CInstruction>& instruction)
{
    // initialize node stack and tokens queue needed for parsing
    std::stack<std::unique_ptr<CASTNode>> node_stack;
    std::deque<Token> tokens_queue(tokens_row.begin(), tokens_row.end());
    // Instruction to be created based on parsed line
    // add line node to the stack
    node_stack.push(std::make_unique<CASTLine>());

    return m_TraverseAST(tokens_queue, node_stack, instruction);
}

bool CParser::m_RemoveLabels(TokenContainer &tokens)
{   
    // map holding 
    std::unordered_map<std::string, int> labels;
    int n = tokens.size();
    for (int i = 0; i < n; i++) 
    {   
        // if first token of the line is label, add it to the map
        if (tokens[i].size() == 0) 
        {
            continue;
        }
        const Token& first_token = tokens[i][0];
        if (first_token.type() != TokenType::LABEL) 
        {
            continue;
        }
        if (labels.find(first_token.value()) != labels.end())
        {
            // if label is redefined throw an error
            int prev_occ = labels[first_token.value()];
            const Token& prevFound = tokens[prev_occ][0];
            LOG_ERR("Error in parsing, line: {}, Label {} already declared in code in line: {}",
                first_token.line(), first_token.value(), prevFound.line());
            return false;
        }
        // psuh label to the labels map
        labels[first_token.value()] = i;
    }
    // after finding labels, and their associated line nums, switch labels names with relative nums
    for (int i = 0; i < tokens.size(); i++) 
    {
        // we can skip first token in line 
        for (int j = 1; j < tokens[i].size(); j++)
        {
            Token& curr = tokens[i][j];
            if (curr.type() != TokenType::LABEL)
            {
                continue;
            }
            // if used label not declared, return false
            if (labels.find(curr.value()) == labels.end())
            {
                LOG_ERR("In line {}, idx {}, using label: {} that has not been previously declared",
                    curr.line(), curr.idx(), curr.value());
                return false;
            }

            int label_declaration_idx = labels[curr.value()];
                        
            std::string label_switch_val = std::to_string(label_declaration_idx - i);
            // change value and type of the token
            curr.SetValue(label_switch_val);
            curr.SetType(TokenType::NUMERICAL_VAL);
            //LOG_WRN("Switched to value {}", curr.value());
            LOG_DBG("Successfully switched label with numerical value in line {}, idx {}", 
                curr.line(), curr.idx());

        }
    }
    // after switching is done we can remove labels declarations from start of the lines
    for (const auto& label : labels) 
    {
        int idx = label.second;
        tokens[idx].erase(tokens[idx].begin());
    }
    return true;
}

bool CParser::m_TraverseAST(std::deque<Token> &tokens, std::stack<std::unique_ptr<CASTNode>> &nodes,
                            std::unique_ptr<CInstruction>& instruction)
{

    if (tokens.size() == 0 && nodes.size() != 0) 
    {
        return false;
    }
    if (tokens.size() != 0 && nodes.size() == 0)
    {
        return false;
    }
    if (tokens.size() == 0 && nodes.size() == 0)
    {
        return true;
    }

    std::unique_ptr<CASTNode> next_node = std::move(nodes.top());
    nodes.pop();

    if (next_node->Eval(tokens, nodes, instruction) == ParseResult::PARSE_FAIL)
    {
        return false;
    }
    return m_TraverseAST(tokens, nodes, instruction);
}
