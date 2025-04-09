#include "GUIToolBar.h"
#include <iostream>

// TODO -> reconsider changing to menu bar
GUIToolBar::GUIToolBar(const QString& name, QWidget* parent) : QToolBar(name, parent) 
{
    m_pause_btn = new QPushButton("PAUSE");
    m_play_btn = new QPushButton("PLAY");
    m_load_btn = new QPushButton("LOAD");
    m_reset_btn = new QPushButton("RESET");
    m_speedup_btn = new QPushButton("Speed up");

    addWidget(m_pause_btn);
    addWidget(m_play_btn);
    addWidget(m_speedup_btn);
    addWidget(m_reset_btn);
    addWidget(m_load_btn);
}
