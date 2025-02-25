#pragma once

#include <QtWidgets>
#include "GUIArena.h"
#include "GUIToolBar.h"
#include "GUIOperationalPanel.h"

class GUIMainWindow : public QMainWindow {
    Q_OBJECT
public:
    GUIMainWindow(int width, int height, QWidget* parent = nullptr);

private:
    GUIArena* m_arena;
    GUIToolBar* m_toolBar;
    GUIOperationalPanel* m_op_panel;
};
