#include "Lexer.h"

Lexer* Lexer::m_instance = nullptr;


Lexer *Lexer::GetInstance()
{
    if (m_instance == nullptr) {
        m_instance = new Lexer{};
    }
    return m_instance;
}