#include "parsing_tests.h"
#include "param_copying.h"
#include "operator_copying.h"
#include "instruction_copying.h"
#include "operations_test_machine.h"
#include "code_loader.h"
#include "default_mod_setter.h"


int main(int argc, char** argv) {
    /* TESTING PARSER */
    ParserTestMachine parser_tests;
    parser_tests.RunTests();
    parser_tests.SetTestsuiteDir("arithm_operations");
    parser_tests.RunTests();
    /* END TESTING PARSER*/
    /* TESTING PARAM COPYING */
    OperationTestingMachine operators_tests;
    operators_tests.RunTests();
    DefaultModSetterTests default_mod_tests;
    default_mod_tests.RunTests();
    /* TESTING FINISHING INSTRUCTION SETUP */
    CodeLoaderTests code_loader_tests;
    code_loader_tests.RunTestsRunner();

    return 0;
}