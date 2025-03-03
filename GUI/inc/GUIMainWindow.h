#pragma once

#include <QtWidgets>
#include "GUIArena.h"
#include "GUIToolBar.h"
#include "GUIOperationalPanel.h"

/// @brief Main window of the application
///
/// Consists of three main elements:
///
/// - Functional buttons
///
/// - Arena
///
/// - Stats panel
///
class GUIMainWindow : public QMainWindow {
    Q_OBJECT
public:
    GUIMainWindow(int width, int height, QWidget* parent = nullptr);

private:
    // widget for arena
    GUIArena* m_arena;
    // widget for functional buttons
    GUIToolBar* m_toolBar;
    // widget for stats panel
    GUIOperationalPanel* m_op_panel;
};
