#include "GUIToolBar.h"
#include <iostream>
#include "logger.h"
#include "GUIUtils.h"
#include "GUIConstants.h"

// TODO -> reconsider changing to menu bar
GUIToolBar::GUIToolBar(const QString& name, QWidget* parent) : QToolBar(name, parent) 
{
    // init buttons
    m_InitButton(m_pause_btn,        "PAUSE");
    m_InitButton(m_play_btn,          "PLAY");
    m_InitButton(m_load_btn,          "LOAD");
    m_InitButton(m_restart_btn,    "RESTART");
    m_InitButton(m_speedup_btn,   "SPEED UP");
    m_InitButton(m_slowdown_btn, "SLOW DOWN");
    // init speed label
    m_InitSpeedLabel();
    // connect speed up buttons to slots
    connect(m_speedup_btn, &QPushButton::pressed, this, &GUIToolBar::SlotSpeedUp);
    connect(m_slowdown_btn, &QPushButton::pressed, this, &GUIToolBar::SlotSlowDown);

    addWidget(m_pause_btn);
    addWidget(m_play_btn);
    addWidget(m_restart_btn);
    addWidget(m_load_btn);
    addWidget(m_slowdown_btn);
    addWidget(m_speedup_btn);
    addWidget(m_game_speed);

    
}

void GUIToolBar::m_InitButton(QPushButton*& btn, const QString& title)
{
    // set fixed size for each button
    LOG_WRN("In button initialization");
    btn = new QPushButton(title, this);
    btn->setFixedSize(GUI::TOOLBAR_BUTTON_WIDTH, GUI::TOOLBAR_BUTTON_HEIGHT);
}

void GUIToolBar::m_InitSpeedLabel()
{
    m_game_speed = new QLabel("SPEED: " + m_play_speed);
    SetColorBase(m_game_speed, QColorConstants::LightGray);
    SetTextColorBase(m_game_speed, QColorConstants::Black);
    m_game_speed->setFixedSize(GUI::TOOLBAR_BUTTON_WIDTH, GUI::TOOLBAR_BUTTON_HEIGHT);
    m_game_speed->setAlignment(Qt::AlignCenter);
    
}

void GUIToolBar::m_AdjustPlaySpeed(bool speedup)
{
    if (m_play_speed == "x0.5")
    {
        // delay equal to 100ms
        m_play_speed = (speedup) ? "x1.0" : "x0.5";
    }
    else if (m_play_speed == "x1.0")
    {
        // delay equal to 50ms is default
        m_play_speed = (speedup) ? "x2.0" : "x0.5";
    }
    else if (m_play_speed == "x2.0")
    {
        // delay equal to 25ms
        m_play_speed = (speedup) ? "x5.0" : "x1.0";
    }
    else if (m_play_speed == "x5.0")
    {
        // delay equal to 10ms
        m_play_speed = (speedup) ? "x10.0" : "x2.0";
    }
    else if (m_play_speed == "x10.0")
    {
        // delay equal to 5ms
        m_play_speed = (speedup) ? "x10.0" : "x5.0";
    }
    m_game_speed->setText("SPEED: " + m_play_speed);
}


void GUIToolBar::SlotSpeedUp()
{
    m_AdjustPlaySpeed(true);
    LOG_WRN("Changed speed of game to {}", m_play_speed.toStdString());
}

void GUIToolBar::SlotSlowDown()
{
    m_AdjustPlaySpeed(false);
    LOG_WRN("Changed speed of game to {}", m_play_speed.toStdString());
}
