#pragma once

#include <QtWidgets>

#include <functional>

#include "logger.h"

/// Interface between logic of the application and GUI. Its main responsibility
/// is to use signals and slots for communication. Logic will send signals 
/// by signing for callbacks
class GUILogicProxy : public QWidget {
    using slot_cb = std::function<void()>;    
    Q_OBJECT
public:
    GUILogicProxy(QWidget* parent = nullptr): QWidget(parent){};

    // callback setters
    void SetPauseGameCb(slot_cb cb) { m_pause_game_cb = cb; };
    void SetLoadGameCb(slot_cb cb) { m_load_game_cb = cb; };
    void SetRestartGameCb(slot_cb cb) { m_restart_game_cb = cb; };
    void SetStartGameCb(slot_cb cb) { m_start_game_cb = cb; };
    // signal senders
    void SendPlayerMoveEvent(int cell, int player_id) { emit SignalPlayerMove(cell, player_id); };
    void SendPlayerLoadEvent(int starting_idx, int instructions_amount, int player_id)  
                            { emit SignalPlayerLoad(starting_idx, instructions_amount, player_id); };

    void TestFunc() { LOG_ERR("TEST LOG"); };
private:
    slot_cb m_pause_game_cb;
    slot_cb m_load_game_cb;
    slot_cb m_restart_game_cb;
    slot_cb m_start_game_cb;

public slots:
    void SlotPauseGame() {};
    void SlotLoadPlayers() { 
        LOG_WRN("In loadPlayers callback");    
        m_load_game_cb(); 
    };
    void SlotRestartGame() {};
    void SlotStartGame() { m_start_game_cb(); };

signals:
    void SignalPlayerMove(int cell, int player_id); // cell to be passed to main menu
    void SignalPlayerLoad(int starting_idx, int instructions_amount, int player_id);
    
};