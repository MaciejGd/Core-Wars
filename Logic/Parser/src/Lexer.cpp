#include "Lexer.h"
#include "logger.h"

#include <fstream>
#include <cerrno>
#include <algorithm>

TokenContainer Lexer::GetTokens(std::string_view file_path)
{
    s_file_name = file_path;
    TokenContainer tokens;
    std::ifstream file_contents{std::string(file_path)};
    if (!file_contents.is_open()) 
    {
        LOG_ERR("Error for path: {} {}", file_path, std::strerror(errno));
        return TokenContainer();
    }
    std::string line;
    int line_counter = 1;
    // analyze file line by line
    while (std::getline(file_contents, line)) 
    {
        m_TokenizeLine(line, tokens, line_counter);
        line_counter++;
    }
    file_contents.close();

    return tokens;
}

void Lexer::m_TokenizeLine(const std::string& line, TokenContainer& tokens, int line_counter) 
{
    std::vector<Token> tokens_row;
    int idx = 0;
    int len = line.size();
    // lambda function for stripping spaces
    auto strip_spaces = [line, &idx, len] () {
        for (; idx < len && (line[idx]== '\t' || line[idx]=='\n' || line[idx]=='\r' 
            || line[idx]=='\b' || line[idx]==' '); idx++);
    };
    // lambda for turning string lower case and adding to token if it is not empty
    auto add_not_empty = [&tokens_row, &idx, line_counter] (auto s) {
        if (s.empty()) 
        {
            return;
        }
        std::transform(s.begin(), s.end(), s.begin(), [](auto c) {
            return std::tolower(c);
        });
        tokens_row.push_back(Token{line_counter, idx, s});
    };

    strip_spaces();
    // string for storing word lexed at the moment
    std::string actual; 
    while (idx < len) 
    {   
        if (findInArray(tkn_address_modes, line[idx]))
        {
            // if address mode sign spotted, add it to vector of token and continue
            add_not_empty(actual);
            actual = "";
            tokens_row.push_back(Token{line_counter, idx+1, TokenType::ADDRESS_MODE, std::string{line[idx]}});
        }
        else if (findInArray(tkn_ar_ops, line[idx]))
        {
            // if arithmetic operator found, add new token
            add_not_empty(actual);
            tokens_row.push_back(Token{line_counter, idx+1, TokenType::ARITHM_OPS, std::string{line[idx]}});
            actual = "";
        }
        else if (findInArray(tkn_separators, line[idx]))
        {
            // if separator found, add new token
            add_not_empty(actual);
            tokens_row.push_back(Token{line_counter, idx+1, TokenType::SEPARATOR, std::string{line[idx]}});
            actual = "";
        }
        else if (line[idx] == ';') 
        {
            // if comment spotted break immidiately
            break;
        }
        else if (line[idx] == '.') 
        {   
            // if we spotted modifier (.) then we can instanly check for next letters
            add_not_empty(actual);
            actual = ".";
        }
        else if (line[idx] == ' ' || line[idx] == '\t' || line[idx] == '\b') 
        {   
            // if white-space add Token to list and skip all white-spaces
            add_not_empty(actual);
            actual = "";
            strip_spaces();
            idx--; // we need to decrement because it is incremented in strip spaces 
                    // as well as in this loop
        }
        else 
        {
            actual+=line[idx];
        }
        idx++;
    }
    add_not_empty(actual);
    // do not add tokens row if it is empty
    if (tokens_row.empty()) 
        return;
    tokens_row.push_back(Token{line_counter, idx+1, TokenType::END_LINE, ""});
    tokens.push_back(std::move(tokens_row));
}