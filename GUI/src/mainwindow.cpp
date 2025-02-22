#include "mainwindow.h"


MainWindow::MainWindow(int width, int height, QWidget* parent): QMainWindow(parent) {
    
    setFixedSize(width, height);

    // set batlle field
    grid = std::make_unique<GuiField>(80, 100);
    setCentralWidget(grid.get());
    // set toolbar
    tool_bar = std::make_unique<ToolBar>("Options");
    addToolBar(tool_bar.get());
}