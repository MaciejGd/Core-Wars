#include "parsing_tests.h"

#include <filesystem>
#include <fstream>
#include <set>

namespace fs = std::filesystem;

void ParserTestMachine::RunTest(const std::string& file_name)
{
    std::string file_path = m_test_path + m_testsuite + file_name;
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
    std::string test_path = m_test_path + m_testsuite;
    // analyze files in alphabetical order so use set
    std::set<std::string> test_files;
    for (const auto& entry : fs::directory_iterator(test_path))
    {
        fs::path test_name = entry.path();
        std::string file_name = test_name.string();
        test_files.insert(file_name);
    }
    for (const auto& file_name : test_files) {
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
    std::vector<std::unique_ptr<CInstruction>> instructions;
    if (CParser::ParseFile(tokens, instructions))
    {
        m_PrintParsedInstructions(instructions); // if succeed then print parsed instructions
        return ";PASS";
    }
    return ";FAIL";
}

void ParserTestMachine::m_PrintParsedInstructions(const std::vector<std::unique_ptr<CInstruction>> &instructions) const 
{
    LOG_PASS("PRINTING PARSED INSTRUCTIONS");
    for (const auto& instruction : instructions)
    {
        LOG_PASS("{}", instruction->PrintInstruction());
    }
    LOG_PASS("END OF PRINTING PARSED INSTRUCTIONS");
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
