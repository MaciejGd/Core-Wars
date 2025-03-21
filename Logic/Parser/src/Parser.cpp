#include "Parser.h"

#include "logger.h"

#include <string>
#include <unordered_map>

void Parser::test_RemoveLables(TokenContainer &tokens)
{
    m_RemoveLabels(tokens);
}

bool Parser::m_RemoveLabels(TokenContainer &tokens)
{   
    // map holding 
    std::unordered_map<std::string, int> labels;
    int n = tokens.size();
    LOG_ERR("BEFORE PARSING LABELS");
    for (int i = 0; i < n; i++) 
    {   
        // if first token of the line is label, add it to the map
        if (tokens[i].size() == 0) 
        {
            continue;
        }
        const Token& first_token = tokens[i][0];
        LOG_ERR("Line size: {}", tokens[i].size());
        if (first_token.type() != TokenType::LABEL) 
        {
            continue;
        }
        if (labels.find(first_token.value()) != labels.end())
        {
            int prev_occ = labels[first_token.value()];
            const Token& prevFound = tokens[prev_occ][0];
            LOG_ERR("Error in parsing, line: {}, Label {} already declared in code in line: {}",
                first_token.line(), first_token.value(), prevFound.line());
            return false;
        }
        // psuh label to the labels map
        labels[first_token.value()] = i;
    }
    LOG_ERR("AFTER PARSING LABELS");
    // after finding labels, and their associated line nums, switch labels with relative nums
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
            // change only value for now as we need to check grammar rules for labels 
            curr.SetValue(label_switch_val);

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