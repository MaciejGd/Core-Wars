#include "mainwindow.h"

const int WIDTH = 1200;
const int HEIGHT = 800;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window(WIDTH, HEIGHT);
    window.show();
    return app.exec();
}