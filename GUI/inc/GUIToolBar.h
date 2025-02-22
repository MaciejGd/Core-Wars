#pragma once
#include <QToolBar>
#include <QString>
#include <QPushButton>
#include <memory>


class GUIToolBar : public QToolBar {
    Q_OBJECT 
    std::unique_ptr<QPushButton> m_choose_btn;
    std::unique_ptr<QPushButton> m_reset_btn;
public:
    GUIToolBar(const QString& name = "", QWidget* parent = nullptr);
};