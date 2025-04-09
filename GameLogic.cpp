#include "GameLogic.h"
#include "logger.h"

#define DEF_PLAYERS_AMOUNT 2

/// @brief obtain ref to Singleton arena and init two default players
GameLogic::GameLogic(): m_arena(CArena::GetInstance())
{
    LOG_DBG("Game logic initialization");
    m_InitPlayers();
    SetGUIProxyCallbacks();
}

void GameLogic::SetGUIProxyCallbacks()
{
    m_gui_proxy.SetStartGameCb([this](){ this->StartGame(); });
    m_gui_proxy.SetLoadGameCb([this](){ this->LoadPlayers(); });
}

void GameLogic::StartGame()
{
    std::vector<bool> finished(m_players.size(), false);
    while (m_running)
    {
        int players_active = 0;
        for(int i = 0; i < m_players.size(); i++)
        {
            // if player already dead, skip him
            if (finished[i] == true)
            {
                continue;
            }
            players_active++;
            // make a player move
            if (!PlayerMove(i))
            {
                finished[i] = true;   
            }
        }
        if (players_active == 0)
        {
            break;
        }
    }
}

void GameLogic::LoadPlayers()
{
    LOG_WRN("In load players callback, main game loop");
    // TODO, change a bit logic of setting string for a player? not necessarily
    m_players[0].SetFileName("../tests/code_loading/test1.txt");
    m_players[1].SetFileName("../tests/code_loading/test2.txt");
    int starting_idx, instructions_amount;
    for (int i = 0; i < PLAYERS_AMOUNT; i++)
    {
        // load code to logic arena
        m_players[i].LoadInitialCode(starting_idx, instructions_amount);
        // send event to GUIArena so it can color cells respectively
        m_gui_proxy.SendPlayerLoadEvent(starting_idx, instructions_amount, i);
    }
    // first load players codes, then start the game
    //StartGame(); TODO
}

bool GameLogic::PlayerMove(int player_id)
{
    // first execute next player's task
    CPlayer& player = m_players[player_id];
    int cell = player.GetPC();
    // send event to GUI
    m_gui_proxy.SendPlayerMoveEvent(cell, player_id);
    // execute operation for player
    if (!player.ExecuteTask())
    {
        LOG_DBG("Wrong operation executed, last process of a player {} got killed!", player_id);
        return false;
    }
    return true;
}

void GameLogic::m_InitPlayers()
{
    LOG_DBG("Initializing {} players", DEF_PLAYERS_AMOUNT);
    m_players.clear();
    for (int i = 0; i < DEF_PLAYERS_AMOUNT; i++)
    {
        // player id will be its index in vector
        m_players.push_back(std::move(CPlayer(i)));
    }
}
