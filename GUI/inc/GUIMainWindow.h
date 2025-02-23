#pragma once

#include <QtWidgets>
#include "GUIArena.h"
#include "GUIToolBar.h"

class GUIMainWindow : public QMainWindow {
    Q_OBJECT
    GUIArena* m_arena;
    GUIToolBar* m_toolBar;
public:
    GUIMainWindow(int width, int height, QWidget* parent = nullptr);
};
