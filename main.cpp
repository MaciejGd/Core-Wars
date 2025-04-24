#include "GUIMainWindow.h"
#include "GameLogic.h"

const int WIDTH = 1400;
const int HEIGHT = 900;

//test
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // initialize game logic object first as it controls lifetime of GUILogicProxy object
    GameLogic game_logic;

    GUIMainWindow window(WIDTH, HEIGHT, game_logic.GetGUILogicProxy());

    // push GUI logic proxy to new thread
    QThread* logic_thread = new QThread{};
    game_logic.GetGUILogicProxy().moveToThread(logic_thread);
    logic_thread->start();

    // show application
    window.show();
    return app.exec();
}