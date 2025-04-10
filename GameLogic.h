#pragma once

#include <QObject>
#include <vector>
#include "Player.h"
#include "Arena.h"
#include "GUILogicProxy.h"

/// Class implementing game logic, sets
/// callback necessary for interactions with GUI
class GameLogic {
public:
    GameLogic();

    /// Sets callbacks of GUI proxy with methods of 
    /// GameLogic class
    void SetGUIProxyCallbacks();

    /// @brief Function implementing game loop
    void RunGameLoop();

    /// @brief  Function to be executed after load players signal from GUI comes
    void LoadPlayers();

    // GUILogic proxy object getter
    GUILogicProxy& GetGUILogicProxy() { return m_gui_proxy; };

    /// Function executing operation for player and passing 
    /// information of execution to GUI 
    /// @param player_id id of player executing operation
    /// @return boolean - true if player still got some processes alive
    /// false otherwise
    bool PlayerMove(int player_id);

    /// @brief Pause execution of main game loop
    void PauseMainLoop();

    /// @brief Resume execution of main game loop
    void ResumeMainLoop();

    /// @brief Callback triggered when instruction data is requested by GUI
    /// @param cell_idx index of memory cell, to get instruction from  
    void SendInstructionDataCb(int cell_idx);
private:
    // inits
    void m_InitPlayers();
    // players
    std::vector<CPlayer> m_players;
    // interface for logic - GUI communication
    GUILogicProxy m_gui_proxy; 
    
    CArena& m_arena;
    // vector indicating if player is dead pr not
    std::vector<bool> m_dead_players;

    int m_active_player = 0;
    bool m_running = true;
};