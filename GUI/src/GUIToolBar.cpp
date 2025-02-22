#include "GUIToolBar.h"


GUIToolBar::GUIToolBar(const QString& name, QWidget* parent) : QToolBar(name, parent) {
    m_choose_btn = std::make_unique<QPushButton>("CHOOSE_FIGHTERS");
    m_reset_btn = std::make_unique<QPushButton>("RESET_ARENA");
    addWidget(m_choose_btn.get());
    addWidget(m_reset_btn.get());
}