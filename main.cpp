#include "GUIMainWindow.h"
#include "GUIFileExplorer.h"
#include "Arena.h"
#include "Lexer.h"
#include "Parser.h"
#include "parsing_tests.h"

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
    ParserTestMachine test_harness;
    //test_harness.SetTestsuiteDir("arithm_operations");
    test_harness.RunTests();
    // CArena ar;
    // ar.TestPrint();
    // QApplication app(argc, argv);
    // GUIMainWindow window(WIDTH, HEIGHT);
    // window.show();
    // return app.exec();
}