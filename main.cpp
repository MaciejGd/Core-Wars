#include "GUIMainWindow.h"
#include "GUIFileExplorer.h"

const int WIDTH = 1400;
const int HEIGHT = 900;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GUIMainWindow window(WIDTH, HEIGHT);
    window.show();
    return app.exec();
}