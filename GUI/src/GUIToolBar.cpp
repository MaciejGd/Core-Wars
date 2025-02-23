#include "GUIToolBar.h"
#include <iostream>

GUIToolBar::GUIToolBar(const QString& name, QWidget* parent) : QToolBar(name, parent) {
    m_choose_btn = new QPushButton("CHOOSE_FIGHTERS");
    m_reset_btn = new QPushButton("RESET_ARENA");

    connect(m_choose_btn, &QPushButton::pressed, this, &GUIToolBar::ChoosePlayersCb);

    addWidget(m_choose_btn);
    addWidget(m_reset_btn);
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