#pragma once
#include <QToolBar>
#include <QString>
#include <QPushButton>
#include <memory>
#include <string>

class ToolBar : public QToolBar {
    Q_OBJECT 
    std::unique_ptr<QPushButton> choose_btn;
    std::unique_ptr<QPushButton> reset_btn;
public:
    ToolBar(const QString& name = "", QWidget* parent = nullptr);
};