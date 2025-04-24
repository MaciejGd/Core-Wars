#include "Parser.h"

#include "logger.h"
#include "ASTLine.h"
#include "ASTExpression.h"
#include "ExprParser.h"

#include <string>
#include <unordered_map>
#include <stack>
#include <deque>


bool CParser::ParseFile(TokenContainer &tokens, std::vector<std::unique_ptr<CInstruction>>& instructions, int &offset)
{
    // first check if TokenContainer is empty, if so, either lexing failed or directory was passed as argument
    if (tokens.size() == 0)
    {
        m_error_msg = "Either file failed to be opened, or directory got chosen. Please choose correct RedCode file";
        return false;
    }
    // clear members before parsing
    m_ClearContainers();
    m_error_msg = "";
    // DEBUG
    m_AnalyzePseudoInstructions(tokens);
    // remove labels from the line starts perform some initial checking
    if (!m_RemoveLabels(tokens))
    {
        return false;
    }
    for (int i = 0; i < tokens.size(); i++)
    {
        PrintTokensLine(tokens[i]);
    }
    
    // count offset value
    offset = m_EvaluateStartIndex();
    LOG_PASS("OFFSET TO PROGRAM START {}", offset);
    // create instructions
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
    std::stack<std::unique_ptr<IASTNode>> node_stack;
    std::deque<Token> tokens_queue(tokens_row.begin(), tokens_row.end());
    // Instruction to be created based on parsed line
    // add line node to the stack
    node_stack.push(std::make_unique<CASTLine>());

    return m_TraverseAST(tokens_queue, node_stack, instruction);
}

bool CParser::m_GatherLabels(TokenContainer& tokens)
{
    // map holding 
    LOG_DBG("Gathering labels");
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
        if (m_labels.find(first_token.value()) != m_labels.end())
        {
            // if label is redefined throw an error
            int prev_occ = m_labels[first_token.value()];
            const Token& prevFound = tokens[prev_occ][0];
            // update error msg
            m_error_msg = std::format("Error in parsing, line: {}, Label {} already declared in code in line: {}",
                first_token.line(), first_token.value(), prevFound.line());
            LOG_ERR(m_error_msg);
            return false;
        }
        // push label to the labels map
        m_labels[first_token.value()] = i;
    }
    return true;
}

bool CParser::m_RemoveLabels(TokenContainer &tokens)
{   
    // gather labels from tokens container
    if (!m_GatherLabels(tokens))
    {
        return false;
    }
    // replace labels with equ expressions
    if (!m_ReplaceLineTagWithEqu()) 
    {
        return false;
    }
    for (const auto& x : m_labels)
    {
        LOG_WRN("Found label: {}", x.first);
    }
    // switch labels in expression indicating start of the program
    if (!m_SwitchLabels(m_prog_start, 0))
    {
        return false;
    }
    // switch labels in container
    if (!m_SwitchLabelsInFile(tokens))
    {
        return false;
    }

    return true;
}

bool CParser::m_SwitchLabelsInFile(TokenContainer &tokens)
{
    for (int i = 0; i < tokens.size(); i++) 
    {
        if (!m_SwitchLabels(tokens[i], i))
        {
            return false;
        }
    }
    // after switching is done we can remove labels declarations from start of the lines
    for (const auto& label : m_labels) 
    {
        int idx = label.second;
        tokens[idx].erase(tokens[idx].begin());
    }
    return true;
}

bool CParser::m_AnalyzePseudoInstructions(TokenContainer &tokens)
{
    // analyze tokens and check for END, ORG or EQU operations
    bool end_analyzing = false;
    // iterator to first element that should not be assembled
    auto end_it = tokens.end();
    std::vector<int> erase_idxs; // we are sure indexes are pushed to vector increasingly
    for (int i = 0; i < tokens.size() && !end_analyzing; i++)
    {
        for (int j = 0; j < tokens[i].size(); j++)
        {
            Token& next_token = tokens[i][j];
            if (next_token.type() != TokenType::OPERATIONS)
            {
                continue;    
            }
            // handle end operation
            if (next_token.value() == "equ")
            {
                // line with EQU should look like this: label EQU new_label/value, so throw error if EQU is not on second position in line
                if (j != 1)
                {
                    m_error_msg = "Label should precede EQU occurence, and it is NOT present!";
                    LOG_ERR(m_error_msg);
                    return false;
                }
                if (tokens[i][j-1].type() != TokenType::LABEL)
                {
                    m_error_msg = std::format("Token preceding EQU pseudo operation should be of type Label, but is: {}", 
                                tokens[i][j-1].TokenTypeToString());
                    LOG_ERR(m_error_msg);
                    return false;
                }
                // if equ is last token in line, return false
                if (j == tokens[i].size() - 1)
                {
                    m_error_msg = "Value, label or expresion expected after EQU pseudo-operation";
                    LOG_ERR(m_error_msg);
                    return false;
                }
                // create new vector from this line from range token + 1 to the end of line
                auto next_it = std::next(tokens[i].begin(), j+1);
                m_equ_map[tokens[i][j-1].value()] = std::vector<Token>(next_it, tokens[i].end()-1);
                erase_idxs.push_back(i); // mark current line for delete
                continue;
            }
            if (next_token.value() == "org")
            {
                // fill prog start vector with rest of tokens in line
                auto current_it = std::next(tokens[i].begin(), j+1);
                m_prog_start = std::deque<Token>(tokens[i].begin() + j + 1, tokens[i].end());
                erase_idxs.push_back(i); // mark current line for delete
                continue;
            }
            if (next_token.value() == "end")
            {
                // if there is some expression after end, we should update m_prog_start vector
                if (j != tokens[i].size()-2)
                {
                    //auto line_it = std::next(tokens[i].begin(), j+1);
                    m_prog_start = std::deque<Token>(tokens[i].begin()+j+1, tokens[i].end());
                }
                // remove all elements after, including this one as nothing should be assembled after end
                tokens.erase(tokens.begin() + i, tokens.end());
                end_analyzing = true; // not sure if needed TODO, remove that and check if still valid
                break;
            }
        }
    }
    LOG_DBG("Size of tokens container after analyzing pseudo instructions: {}", tokens.size());
    int erase_idx = erase_idxs.size()-1;
    if (erase_idx < 0) return true;
    for (; erase_idx >= 0; erase_idx--)
    {
        // remove line from tokens list
        LOG_DBG("Removing line at index {}", erase_idxs[erase_idx]);
        tokens.erase(tokens.begin() + erase_idxs[erase_idx]);
    }
    return true;
}

int CParser::m_EvaluateStartIndex()
{
    int res = 0;
    // if there is no offset specified quit immidiately
    if (m_prog_start.size() == 0) 
    {
        return 0;
    }
    // parse arithmetic expression
    CExprParser arithm_parser;
    if (arithm_parser.EvaluateExpression(m_prog_start, res) == ParseResult::PARSE_OK)
    {
        return res;
    }
    return 0;
}

bool CParser::m_TraverseAST(std::deque<Token> &tokens, std::stack<std::unique_ptr<IASTNode>> &nodes,
                            std::unique_ptr<CInstruction>& instruction)
{
    // check recursion breaking conditions
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

    std::unique_ptr<IASTNode> next_node = std::move(nodes.top());
    nodes.pop();
    // evaluate next token
    if (next_node->Eval(tokens, nodes, instruction, m_error_msg) == ParseResult::PARSE_FAIL)
    {
        return false;
    }
    return m_TraverseAST(tokens, nodes, instruction);
}

void CParser::m_ClearContainers()
{
    m_equ_map.clear();
    m_prog_start.clear();
    m_labels.clear();
}

bool CParser::m_ReplaceLineTagWithEqu()
{
    // if we have labels map, we should switch all labels if they are in equ map
    for (const auto& equ : m_equ_map)
    {
        std::string label_name = equ.first;
        if (m_labels.find(label_name) == m_labels.end())
        {
            continue;
        }
        // we can switch label with label only, so throw an error when vector len is bigger than one
        // and first token is not label
        if (equ.second.size() != 1 || equ.second[0].type() != TokenType::LABEL)
        {
            m_error_msg = std::format("Cannot switch label line tag at line: {} with \"{}\"", m_labels[label_name], StrTokensLine(equ.second));
            LOG_ERR(m_error_msg);
            return false;
        }
        // switch labels
        m_labels[equ.second[0].value()] = m_labels[label_name];
        // remove original 
        m_labels.erase(label_name);
    }
    LOG_PASS("Properly replaced tag");
    return true;
}
