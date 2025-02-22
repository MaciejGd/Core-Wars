#include "tool_bar.h"


ToolBar::ToolBar(const QString& name, QWidget* parent) : QToolBar(name, parent) {
    choose_btn = std::make_unique<QPushButton>("CHOOSE_FIGHTERS");
    reset_btn = std::make_unique<QPushButton>("RESET_ARENA");
    addWidget(choose_btn.get());
    addWidget(reset_btn.get());
}