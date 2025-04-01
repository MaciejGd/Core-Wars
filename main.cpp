#include "GUIMainWindow.h"
#include "GUIFileExplorer.h"
#include "Arena.h"
#include "Lexer.h"
#include "Parser.h"

// testing
#include "parsing_tests.h"
#include "param_copying.h"
#include "operator_copying.h"
#include "instruction_copying.h"
#include "mov_operator.h"
#include "dat_operator.h"
#include "jmz_operator.h"
#include "jmn_operator.h"
#include "jmp_operator.h"
#include "djn_operator.h"

const int WIDTH = 1400;
const int HEIGHT = 900;

const char* path = "/home/maciekzgk/code/cpp/studia/qt_project/test.txt";

//test
int main(int argc, char *argv[])
{
    // Lexer lexer;
    // TokenContainer tokens = lexer.GetTokens(path);
    // Parser parser;
    // if (parser.ParseFile(tokens)) {
    //     LOG_DBG("Correctly parsed the input file {}", path);
    // }
    // else {
    //     LOG_ERR("Failed to parse input file {}", path);
    // }
    /* TESTING PARSER */
    // ParserTestMachine test_harness;
    // test_harness.RunTests();
    // test_harness.SetTestsuiteDir("arithm_operations");
    // test_harness.RunTests();
    /* END TESTING PARSER*/
    /* TESTING PARAM COPYING */
    // MOVOperatorTest::RunTests();
    // DATOperatorTest::RunTests();
    // JMZOperatorTest::RunTests();
    // JMNOperatorTest::RunTests();
    DJNOperatorTest::RunTests();
    // CArena ar;
    // ar.TestPrint();
    // QApplication app(argc, argv);
    // GUIMainWindow window(WIDTH, HEIGHT);
    // window.show();
    // return app.exec();
    return 0;
}