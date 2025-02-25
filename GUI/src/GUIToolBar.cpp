#include "GUIToolBar.h"
#include <iostream>

// reconsider changing to menu bar
GUIToolBar::GUIToolBar(const QString& name, QWidget* parent) : QToolBar(name, parent) {
    m_stop_btn = new QPushButton("CHOOSE_FIRST_FIGHTER");
    m_play_btn = new QPushButton("CHOOSE_SECOND_FIGHTER");
    m_reset_btn = new QPushButton("RESET_ARENA");
    m_speedup_btn = new QPushButton("Speed up");

    connect(m_stop_btn, &QPushButton::pressed, this, &GUIToolBar::ChoosePlayersCb);
    connect(m_play_btn, &QPushButton::pressed, this, &GUIToolBar::ChoosePlayersCb);

    addWidget(m_stop_btn);
    addWidget(m_play_btn);
    addWidget(m_speedup_btn);
    addWidget(m_reset_btn);
}

// slots
void GUIToolBar::ResetButtonCb() {
    std::cout << "ResetButtonCb\n";
}

void GUIToolBar::ChoosePlayersCb() {
    // TODO reimplement to speed control
}
// this will be removed from here and place in separate widget, with read-only textfield
void GUIToolBar::PlayerPathChangedCb(QString& path) {
    // dummy implementation
    std::cout << "File path is: " << path.toStdString() << std::endl;
}