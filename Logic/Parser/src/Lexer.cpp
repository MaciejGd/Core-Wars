#include "Lexer.h"
#include "logger.h"

#include <fstream>
#include <cerrno>
#include <algorithm>

Lexer* Lexer::m_instance = nullptr;

Lexer *Lexer::GetInstance()
{
    if (m_instance == nullptr) {
        m_instance = new Lexer{};
    }
    return m_instance;
}

const TokenContainer Lexer::GetTokens(std::string_view file_path)
{
    TokenContainer tokens;
    std::ifstream file_contents{std::string(file_path)};
    if (!file_contents.is_open()) 
    {
        LOG_ERR("Error for path: {} {}", file_path, std::strerror(errno));
        return TokenContainer();
    }
    std::string line;
    int line_counter = 1;
    while (std::getline(file_contents, line)) 
    {
        if (line.empty()) 
        {
            continue;
        }
        m_TokenizeLine(line, tokens, line_counter);
        line_counter++;
    }
    LOG_DBG("END");
    file_contents.close();

    /// DEBUG
    for (int i = 0; i < tokens.size(); i++){
    for (int j = 0; j < tokens[i].size(); j++) 
    {
        LOG_DBG("Token lexed: {}", tokens[i][j].PrintFormat());
    }}
    LOG_DBG("Tokenized file: {}", file_path);
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
        std::cout << "In lambda " << s << std::endl;
        tokens_row.push_back(Token{line_counter, idx, s});
    };

    strip_spaces();
    // string for storing word lexed at the moment
    std::string actual; 
    while (idx < len) 
    {   
        // if address mode sign spotted, add it to vector of token and continue
        if (std::find(tkn_address_modes.begin(), tkn_address_modes.end(), line[idx]) != tkn_address_modes.end()) 
        {
            add_not_empty(actual);
            actual = "";
            tokens_row.push_back(Token{line_counter, idx+1, TokenType::ADDRESS_MODE, std::string{line[idx]}});
        }
        else if (std::find(tkn_ar_ops.begin(), tkn_ar_ops.end(), line[idx]) != tkn_ar_ops.end()) 
        {
            add_not_empty(actual);
            tokens_row.push_back(Token{line_counter, idx+1, TokenType::ARITHM_OPS, std::string{line[idx]}});
            actual = "";
        }
        // if coma spotted, add token to the list and continue
        else if (line[idx] == tkn_coma) {
            add_not_empty(actual);
            // add token with separator
            tokens_row.push_back(Token{line_counter, idx+1, TokenType::SEPARATOR, std::string{line[idx]}});
            actual = "";
        }
        else if (line[idx] == ';') // if comment spotted break immidiately
        {
            break;
        }
        // if we spotted modifier (.) then we can instanly check for next letters
        else if (line[idx] == '.') 
        {   
            add_not_empty(actual);
            // start lexing modifier
            actual = ".";
        }
        // if white-space add Token to list and skip all white-spaces
        else if (line[idx] == ' ' || line[idx] == '\t' || line[idx] == '\b') 
        {   
            add_not_empty(actual);
            actual = "";
            strip_spaces();
            idx--; // need to decrement in here as we will increment it 
        }
        else 
        {
            actual+=line[idx];
        }
        idx++;
    }
    add_not_empty(actual);
    tokens.push_back(std::move(tokens_row));
}