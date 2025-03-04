#include "GUIToolBar.h"
#include <iostream>

// TODO -> reconsider changing to menu bar
GUIToolBar::GUIToolBar(const QString& name, QWidget* parent) : QToolBar(name, parent) 
{
    m_stop_btn = new QPushButton("CHOOSE_FIRST_FIGHTER");
    m_play_btn = new QPushButton("CHOOSE_SECOND_FIGHTER");
    m_reset_btn = new QPushButton("RESET_ARENA");
    m_speedup_btn = new QPushButton("Speed up");

    addWidget(m_stop_btn);
    addWidget(m_play_btn);
    addWidget(m_speedup_btn);
    addWidget(m_reset_btn);
}