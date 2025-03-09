#pragma once



/// @brief Singleton for creating token list from input file
class Lexer {
public:
    Lexer* GetInstance();
private:
    Lexer();
    static Lexer* m_instance;
};