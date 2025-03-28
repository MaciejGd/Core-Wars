#pragma once

#include "Lexer.h"
#include "Parser.h"
#include <string_view>

class ParserTestMachine {
public:
    ParserTestMachine() = default;
    void RunTest(const std::string& file_name);
    void RunTests();
    void SetTestsuiteDir(std::string_view testsuite_dir) { m_testsuite = testsuite_dir; };
private:
    const std::string m_test_path = "../tests/";
    std::string m_testsuite = "parsing_tests";

    CLexer m_lexer;

    std::string m_GetParsingResult(const std::string& file_name);
    bool m_CompareResults(const std::string& file_path, const std::string& parsing_result);
};

