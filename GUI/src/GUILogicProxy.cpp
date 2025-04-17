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

void GUILogicProxy::SlotLoadPlayers(const std::vector<std::string>& paths) 
{ 
    LOG_WRN("Execute load players code callback");
    m_load_game_cb(paths); 
}

void GUILogicProxy::SlotRestartGame() 
{
    LOG_DBG("Pausing main game loop"); 
    m_restart_game_cb();
}


void GUILogicProxy::SlotStartGame() 
{
    LOG_DBG("Start/resume main game loop"); 
    m_start_game_cb(); 
}

void GUILogicProxy::SlotInstructionData(int cell_idx)
{
    LOG_DBG("Instruction data at index {}, requested by the user.", cell_idx);
    m_instruction_data_cb(cell_idx);
}

void GUILogicProxy::SlotSpeedUpGame()
{
    m_speedup_game_cb();
}