#include "GUIMainWindow.h"
#include "GUIFileExplorer.h"

const int WIDTH = 1200;
const int HEIGHT = 800;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GUIMainWindow window(WIDTH, HEIGHT);
    window.show();
    return app.exec();
}