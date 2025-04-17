#include "GameLogic.h"
#include "logger.h"
#include <chrono>

#define DEF_PLAYERS_AMOUNT 2
#define TIME_DELAY 50

/// @brief obtain ref to Singleton arena and init two default players
GameLogic::GameLogic(): m_arena(CArena::GetInstance())
{
    LOG_DBG("Game logic initialization");
    m_arena.ClearArena(); // make sure arena is initialized just after launching app
    m_InitPlayers();
    SetGUIProxyCallbacks();
}

void GameLogic::SetGUIProxyCallbacks()
{
    m_gui_proxy.SetStartGameCb([this](){ this->RunGameLoop(); });
    m_gui_proxy.SetPauseGameCb([this](){ this->PauseMainLoop(); });
    m_gui_proxy.SetStartGameCb([this](){ this->ResumeMainLoop(); });
    m_gui_proxy.SetSpeedUpGameCb([this](){ this->SpeedUpGame(); });
    m_gui_proxy.SetInstrDataCb([this](int cell_idx){ this->SendInstructionDataCb(cell_idx); });
    m_gui_proxy.SetRestartGameCb([this](){ this->RestartGame(); });
    m_gui_proxy.SetLoadGameCb([this](const std::vector<std::string>& paths){ this->LoadPlayers(paths); });
}

void GameLogic::RunGameLoop()
{
    std::vector<bool> finished(m_players.size(), false);
    auto start = std::chrono::steady_clock::now();
    auto end = start; 
    
    while (m_running)
    {
        // at first poll events coming to GUIProxy
        m_gui_proxy.CheckPendingEvents(); 
        // slow down program execution
        end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (elapsed.count() <= m_time_delay)
        {
            continue;
        }
        start = end;

        int players_active = 0;
        int last_player_active = 0;
        for(m_active_player; m_active_player < m_players.size() && m_running; m_active_player++)
        {
            // if player already dead, skip him
            if (finished[m_active_player] == true)
            {
                continue;
            }
            players_active++;
            // make a player move
            if (!PlayerMove(m_active_player))
            {
                finished[m_active_player] = true;   
                players_active--;
            }
            else {
                last_player_active = m_active_player;
            }
        }
        if (m_active_player == PLAYERS_AMOUNT) 
        {
            // reset players if all had their turn
            m_active_player = 0;
            // increase rounds counter if all players moved
            m_rounds_last++; 
            m_gui_proxy.SendCounter(m_rounds_last);
        }
        if (players_active <= 1)
        {
            LOG_DBG("Only one player left, quit, player {} won!!!", last_player_active);
            break;
        }
    }
}

void GameLogic::LoadPlayers(const std::vector<std::string>& paths)
{
    for (auto& path : paths)
    {
        LOG_ERR("Path retrieved: {}", path);
    }
    LOG_WRN("In load players callback, main game loop");
    // TODO, change a bit logic of setting string for a player? not necessarily
    m_players[0].SetFileName("../tests/code_loading/test1.txt");
    m_players[1].SetFileName("../tests/code_loading/test2.txt");
    // check if paths amount is equal to players, if not return
    // To be done in final version
    // if (paths.size() != m_players.size())
    // {
    //     LOG_ERR("Paths passed not equal to ");
    // }
    // for (int i = 0; i < m_players.size(); i++)
    // {
    //     m_players[i].SetFileName(paths[i]);
    // }

    int starting_idx, instructions_amount;
    for (int i = 0; i < PLAYERS_AMOUNT; i++)
    {
        // load code to logic arena
        m_players[i].LoadInitialCode(starting_idx, instructions_amount);
        // send event to GUIArena so it can color cells respectively
        m_gui_proxy.SendPlayerLoadEvent(starting_idx, instructions_amount, i);
    }
    // first load players codes, then start the game
    //RunGameLoop(); // TODO
}

bool GameLogic::PlayerMove(int player_id)
{
    CPlayer& player = m_players[player_id];
    int cell = player.GetPC();
    // should be set to -1!!! then it will be checked in GUIArena as not modified
    int modified_cell = -1;
    std::string executed_instruction = m_arena[cell]->PrintInstruction();
    // execute operation for player
    bool operation_result = player.ExecuteTask(modified_cell);
    // send event to GUI
    m_gui_proxy.SendPlayerMoveEvent(cell, player_id, modified_cell, executed_instruction);
    if (!operation_result)
    {
        LOG_DBG("Wrong operation executed, last process of a player {} got killed!", player_id);
        return false;
    }
    LOG_WRN("After player move execution, player_id {}", player_id);
    return true;
}

void GameLogic::PauseMainLoop() 
{ 
    m_running = false; 
}

void GameLogic::ResumeMainLoop() 
{
    m_running = true;
    RunGameLoop();
}

void GameLogic::RestartGame()
{
    // clear arena to whole DAT #0, #0
    m_arena.ClearArena();
}

void GameLogic::SpeedUpGame()
{
    switch (m_time_delay)
    {
        case 50:
            m_time_delay = 25;
            break;
        case 25:
            m_time_delay = 10;
            break;
        case 10:
            m_time_delay = 5;
            break;
        default:
            m_time_delay = 25;
            break;
    }
    LOG_ERR("Time delay is equal to: {}", m_time_delay);
}

void GameLogic::SendInstructionDataCb(int cell_idx)
{
    if (cell_idx < 0 || cell_idx >= ARENA_SIZE)
    {
        LOG_ERR("Requested cell_idx out of arena bounds!");
        return;
    }
    std::string instr_info = m_arena[cell_idx]->PrintInstruction();

    m_gui_proxy.SendInstructionData(instr_info, cell_idx);
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
