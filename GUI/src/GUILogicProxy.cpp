#include "GUILogicProxy.h"

void GUILogicProxy::CheckPendingEvents()
{
    // poll events for thread
    QCoreApplication::processEvents();
}

void GUILogicProxy::SlotPauseGame() 
{ 
    LOG_DBG("Pausing main game loop"); 
    m_pause_game_cb();
}

void GUILogicProxy::SlotLoadPlayers() 
{ 
    LOG_WRN("Execute load players code callback");
    m_load_game_cb(); 
}

void GUILogicProxy::SlotRestartGame() 
{
    LOG_DBG("Pausing main game loop"); 
    m_pause_game_cb();
}


void GUILogicProxy::SlotStartGame() 
{
    LOG_DBG("Start/resume main game loop"); 
    m_start_game_cb(); 
}
