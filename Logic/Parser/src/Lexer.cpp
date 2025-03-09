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

const std::vector<Token> Lexer::GetTokens(std::string_view file_path)
{
    std::vector<Token> tokens;
    std::ifstream file_contents{std::string(file_path)};
    if (!file_contents.is_open()) 
    {
        LOG_ERR("Error for path: {} {}", file_path, std::strerror(errno));
        return std::vector<Token>();
    }
    std::string line;
    while (std::getline(file_contents, line)) 
    {
        if (line.empty()) 
        {
            continue;
        }
        m_TokenizeLine(line, tokens);
        LOG_ERR("In getline loop")
    }
    LOG_DBG("END");
    file_contents.close();

    /// DEBUG
    for (int i = 0; i < tokens.size(); i++) 
    {
        LOG_DBG("Token lexed: {}", tokens[i].PrintFormat());
    }

    return std::vector<Token>();
}

void Lexer::m_TokenizeLine(const std::string& line, std::vector<Token>& tokens) 
{
    int idx = 0;
    int len = line.size();
    // lambda function for stripping spaces
    auto strip_spaces = [line, &idx, len] () {
        for (; idx < len && (line[idx]== '\t' || line[idx]=='\n' || line[idx]=='\r' 
            || line[idx]=='\b' || line[idx]==' '); idx++);
    };
    // lambda for turning string lower case and adding to token if it is not empty
    auto add_not_empty = [&tokens] (auto s) {
        if (s.empty()) 
        {
            return;
        }
        std::transform(s.begin(), s.end(), s.begin(), [](auto c) {
            return std::tolower(c);
        });
        tokens.push_back(Token{s});
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
            tokens.push_back(Token{TokenType::ADDRESS_MODE, std::string{line[idx]}});
        }
        // if coma spotted, add token to the list and continue
        else if (line[idx] == tkn_coma) {
            add_not_empty(actual);
            // add token with separator
            tokens.push_back(Token{TokenType::SEPARATOR, std::string{line[idx]}});
            actual = "";
        }
        else if (line[idx] == ';') 
        {
            add_not_empty(actual);
            return;
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
}