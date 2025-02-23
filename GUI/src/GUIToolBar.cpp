#include "GUIToolBar.h"
#include <iostream>

GUIToolBar::GUIToolBar(const QString& name, QWidget* parent) : QToolBar(name, parent) {
    m_choose_btn = std::make_unique<QPushButton>("CHOOSE_FIGHTERS");
    m_reset_btn = std::make_unique<QPushButton>("RESET_ARENA");

    connect(m_choose_btn.get(), &QPushButton::pressed, this, &GUIToolBar::ChoosePlayersCb);

    addWidget(m_choose_btn.get());
    addWidget(m_reset_btn.get());
}

void GUIToolBar::ChoosePlayersCb() {
    //m_choose_btn
    std::cout << "Players choose callback\n";
    m_file_explorer = std::make_unique<GUIFileExplorer>();
    m_file_explorer->show();
}

void GUIToolBar::ResetButtonCb() {
    std::cout << "ResetButtonCb\n";

}