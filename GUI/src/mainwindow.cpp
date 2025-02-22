#include "mainwindow.h"
#include "gui_field.h"

MainWindow::MainWindow(int argc, char** argv, QWidget* parent): QMainWindow(parent) {
    grid = std::make_unique<GuiField>(100, 80);
    setCentralWidget(grid.get());
}