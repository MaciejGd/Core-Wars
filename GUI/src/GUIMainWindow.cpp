#include "GUIMainWindow.h"

GUIMainWindow::GUIMainWindow(int width, int height, QWidget* parent): QMainWindow(parent) {
    setWindowTitle("Core Wars");
    setFixedSize(width, height);

    // set batlle field
    m_arena = std::make_unique<GUIArena>(80, 100);
    setCentralWidget(m_arena.get());
    // set GUIToolBar
    m_toolBar = std::make_unique<GUIToolBar>("Options");
    addToolBar(m_toolBar.get());
}