#include "GameLogic.h"
#include "logger.h"
#include <chrono>
#include <array>

#define PLAYERS_AMOUNT 2
#define MAX_ROUNDS 8000
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
    m_gui_proxy.SetSpeedUpGameCb([this](){ this->ChangeGameSpeed(true); });
    m_gui_proxy.SetSlowDownGameCb([this](){ this->ChangeGameSpeed(false); });
    m_gui_proxy.SetInstrDataCb([this](int cell_idx){ this->SendInstructionDataCb(cell_idx); });
    m_gui_proxy.SetRestartGameCb([this](){ this->RestartGame(); });
    m_gui_proxy.SetLoadGameCb([this](const std::vector<std::string>& paths){ this->LoadPlayers(paths); });
}

void GameLogic::RunGameLoop()
{
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
        // end battle as a draw if rounds counter is greater than max limit
        if (m_rounds_last >= MAX_ROUNDS)
        {
            LOG_DBG("None of the players won over {} rounds, result of fight is a draw", MAX_ROUNDS);
            std::string info_msg = std::format("None of the players won over {} rounds\n Result of the battle is a draw", MAX_ROUNDS);
            m_gui_proxy.SendShowInfoDialog(info_msg, false);
            return;
        }

        int players_active = 0;
        int last_player_active = 0;
        for(m_active_player; m_active_player < m_players.size() && m_running; m_active_player++)
        {
            // if player already dead, skip him
            if (m_dead_players[m_active_player] == true)
            {
                continue;
            }
            players_active++;
            // make a player move
            if (!PlayerMove(m_active_player))
            {
                LOG_WRN("Killed player {} process", m_active_player);
                m_dead_players[m_active_player] = true;   
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
        }
        if (players_active <= 1 && m_running == true)
        {
            LOG_DBG("Only one player left, quit, player {} won!!!", last_player_active);
            std::string info_msg = std::format("Player {} won!!!", last_player_active);
            m_gui_proxy.SendShowInfoDialog(info_msg);
            // unload players
            m_loaded = false;
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
    if (paths.size() != m_players.size())
    {
        LOG_ERR("Paths for not all players has been set!!!");
        return;
    }
    for (int i = 0; i < paths.size(); i++)
    {
        m_players[i].SetFileName(paths[i]);
    }
    // m_players[0].SetFileName("../tests/code_loading/test1.txt");
    // m_players[1].SetFileName("../tests/code_loading/test2.txt");
    // parse players and load code to Core
    m_running = false; // pause game
    LoadPlayersCode();
}

void GameLogic::LoadPlayersCode()
{
    // reset rounds of the battle
    m_dead_players = std::vector<bool>(m_players.size(), false);
    m_arena.ClearArena();
    m_rounds_last = 0;
    // store starting idx, instructions amount and offset of each player in a array
    std::vector<std::array<int,3>> players_data(PLAYERS_AMOUNT, {0,0,0});
    std::string error_msg = "";
    for (int i = 0; i < PLAYERS_AMOUNT; i++)
    {
        // load code to logic arena
        // if failed to parse input file, abort whole operation
        if (!m_players[i].LoadInitialCode(players_data[i][0], players_data[i][1], players_data[i][2]))
        {
            LOG_ERR("Parsing file for player {} failed", i);
            error_msg += "Parsing error in " + m_players[i].GetFileName() + ":\n " + m_players[i].GetErrorMessage();
            error_msg += "\n\n";
        }
    }
    // if error is not empty, some parsing failed so we should abort whole operation
    if (error_msg != "")
    {
        m_gui_proxy.SendShowInfoDialog(error_msg, true);
        return;
    }
    
    // send signal to load players code if parsing of all warriors succeed
    for (int i = 0; i < PLAYERS_AMOUNT; i++)
    {
        m_gui_proxy.SendPlayerLoadEvent(players_data[i][0], players_data[i][1], i, players_data[i][2]);
    }
    LOG_DBG("Loading players to Core succeeded, send info to GUI");
    m_loaded = true;
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
    LOG_WRN("Sending player move to GUI: pc:{}, player:{}, modified cell: {}, exe instr: {}", cell, player_id, modified_cell, executed_instruction);
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
    if (m_loaded == false)
    {
        LOG_ERR("Programs for players has not been loaded to Core yet, aborting operation");
        std::string info_msg = "Warriors has not been loaded to Core, please choose warriors first";
        m_gui_proxy.SendShowInfoDialog(info_msg, true);
        return;
    } 
    m_running = true;
    RunGameLoop();
}

void GameLogic::RestartGame()
{
    // clean up arena
    //m_arena.ClearArena();
    // load code for players back on arena 
    LoadPlayersCode();
}

void GameLogic::ChangeGameSpeed(bool speedup)
{
    switch (m_time_delay)
    {
        case 100:
            m_time_delay = (speedup) ? 50 : 100;
            break;
        case 50:
            m_time_delay = (speedup) ? 25 : 100;
            break;
        case 25:
            m_time_delay = (speedup) ? 10 : 50;
            break;
        case 10:
            m_time_delay = (speedup) ? 5  : 25;
            break;
        default:
            m_time_delay = (speedup) ? 5 : 10;
            break;
    }
    LOG_ERR("Time delay is equal to: {}ms", m_time_delay);
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
    LOG_DBG("Initializing {} players", PLAYERS_AMOUNT);
    m_players.clear();
    for (int i = 0; i < PLAYERS_AMOUNT; i++)
    {
        // player id will be its index in vector
        m_players.push_back(std::move(CPlayer(i)));
    }
}
