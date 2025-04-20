#include "GUIMainWindow.h"
#include "GUIFileExplorerDialog.h"
#include "GUILogicProxy.h"
#include "Arena.h"
#include "Lexer.h"
#include "Parser.h"
#include "GameLogic.h"

// testing
#include "parsing_tests.h"
#include "param_copying.h"
#include "operator_copying.h"
#include "instruction_copying.h"
#include "operations_test_machine.h"
#include "code_loader.h"
#include "default_mod_setter.h"

const int WIDTH = 1400;
const int HEIGHT = 900;

const char* path = "/home/maciekzgk/code/cpp/studia/qt_project/test.txt";

//test
int main(int argc, char *argv[])
{
    /* TESTING PARSER */
    // ParserTestMachine test_harness;
    // //test_harness.RunTests();
    // test_harness.SetTestsuiteDir("arithm_operations");
    // test_harness.RunTests();
    // return 0;
    /* END TESTING PARSER*/
    /* TESTING PARAM COPYING */
    // OperationTestingMachine operators_tests{};
    // operators_tests.RunTests();
    // DefaultModSetterTests tests;
    // tests.RunTests();

    /* TESTING FINISHING INSTRUCTION SETUP */
    // CodeLoaderTests tests;
    // tests.RunTestsRunner();

    
    /* PSEUDO INSTRUCTIONS */
    CCodeBuilder code_builder;
    int offset = 0;
    // code_builder.ProduceInstructions("../tests/code_loading/equ_test.txt", offset);
    code_builder.ProduceInstructions("../tests/code_loading/test2.txt", offset);
    return 0;
    /* RUNNING GUI */    
    // Application    
    QApplication app(argc, argv);

    GameLogic game_logic;
    QThread* logic_thread = new QThread{};

    GUIMainWindow window(WIDTH, HEIGHT, game_logic.GetGUILogicProxy());

    game_logic.GetGUILogicProxy().moveToThread(logic_thread);

    logic_thread->start();

    window.show();
    return app.exec();
    return 0;
}