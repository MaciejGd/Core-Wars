#include "GUIMainWindow.h"
#include "GUIFileExplorer.h"
#include "Arena.h"
#include "Lexer.h"

const int WIDTH = 1400;
const int HEIGHT = 900;

const char* path = "/home/maciekzgk/code/cpp/studia/qt_project/test.txt";


int main(int argc, char *argv[])
{
    Lexer* lexer = Lexer::GetInstance();
    lexer->GetTokens(path);
    // CArena ar;
    // ar.TestPrint();
    // QApplication app(argc, argv);
    // GUIMainWindow window(WIDTH, HEIGHT);
    // window.show();
    // return app.exec();
}