#include "parsing_tests.h"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void ParserTestMachine::RunTest(const std::string& file_name)
{
    std::string file_path = m_test_path + file_name;
    std::string result = m_GetParsingResult(file_path);
    if (m_CompareResults(file_path, result))
    {
        LOG_PASS("testcase: {} [PASSED]", file_name);
    }
    else 
    {
        LOG_FAIL("testcase: {} [FAILED]", file_name);
    }
}


void ParserTestMachine::RunTests()
{
    for (const auto& entry : fs::directory_iterator(m_test_path))
    {
        fs::path test_name = entry.path();
        std::string file_name = test_name.string();
        std::string result = m_GetParsingResult(file_name);
        if (m_CompareResults(file_name, result))
        {
            LOG_PASS("testcase: {} [PASSED]", file_name);
        }
        else 
        {
            LOG_FAIL("testcase: {} [FAILED]", file_name);
        }
    }
}

std::string ParserTestMachine::m_GetParsingResult(const std::string &file_name)
{
    TokenContainer tokens = m_lexer.GetTokens(file_name);
    std::string result = "";
    if (m_parser.ParseFile(tokens))
    {
        return ";PASS";
    }
    return ";FAIL";
}

bool ParserTestMachine::m_CompareResults(const std::string &file_path, const std::string& parsing_result)
{
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        LOG_ERR("Failed to open {} for testing purposes", file_path);
        return false;
    }
    std::string first_line;
    std::getline(file, first_line);
    // trim whitespaces
    auto start = std::find_if_not(first_line.begin(), first_line.end(), ::isspace);
    auto end = std::find_if_not(first_line.rbegin(), first_line.rend(), ::isspace).base();
    first_line = std::string(start, end);
    if (first_line == parsing_result)
    {
        return true;
    }
    return false;
}
