#pragma once

#include <QtWidgets>
#include <memory>
#include "GUIArena.h"
#include "GUIToolBar.h"


class GUIMainWindow : public QMainWindow {
    Q_OBJECT
    std::unique_ptr<GUIArena> m_arena;
    std::unique_ptr<GUIToolBar> m_toolBar;
public:
    GUIMainWindow(int width, int height, QWidget* parent = nullptr);
};
