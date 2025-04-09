#pragma once

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
    void StartGame();

    /// @brief  Function to be executed after load players signal from GUI comes
    void LoadPlayers();


    GUILogicProxy& GetGUILogicProxy() { return m_gui_proxy; };
    /// Function executing operation for player and passing 
    /// information of execution to GUI 
    /// @param player_id id of player executing operation
    /// @return boolean - true if player still got some processes alive
    /// false otherwise
    bool PlayerMove(int player_id);
private:
    // inits
    void m_InitPlayers();
    // players
    std::vector<CPlayer> m_players;
    // interface for logic - GUI communication
    GUILogicProxy m_gui_proxy; 
    
    CArena& m_arena;

    bool m_running = true;
};