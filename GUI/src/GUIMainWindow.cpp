#include "GUIMainWindow.h"

GUIMainWindow::GUIMainWindow(int width, int height, QWidget* parent): QMainWindow(parent) {
    setWindowTitle("Core Wars");
    setFixedSize(width, height);

    // set batlle field
    m_arena = new GUIArena(80, 100);
    setCentralWidget(m_arena);
    // set GUIToolBar
    m_toolBar = new GUIToolBar("Options");
    addToolBar(m_toolBar);
}