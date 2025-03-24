#pragma once

#include "Lexer.h"
#include "Parser.h"

class ParserTestMachine {
public:
    ParserTestMachine() = default;
    void RunTest(const std::string& file_name);
    void RunTests();
private:
    const std::string m_test_path = "../tests/parsing_tests/";

    CLexer m_lexer;
    Parser m_parser;

    std::string m_GetParsingResult(const std::string& file_name);
    bool m_CompareResults(const std::string& file_path, const std::string& parsing_result);
};

