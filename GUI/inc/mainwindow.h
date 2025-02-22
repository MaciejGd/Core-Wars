#pragma once

#include <QtWidgets>
#include <memory>
#include "gui_field.h"
#include "tool_bar.h"


class MainWindow : public QMainWindow {
    Q_OBJECT
    std::unique_ptr<GuiField> grid;
    std::unique_ptr<ToolBar> tool_bar;
public:
    MainWindow(int width, int height, QWidget* parent = nullptr);
};
