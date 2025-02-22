#pragma once

#include <QtWidgets>
#include <memory>


class MainWindow : public QMainWindow {
    Q_OBJECT
    std::unique_ptr<GuiField> grid;
public:
    MainWindow(int argc, char** argv, QWidget* parent = nullptr);
};
