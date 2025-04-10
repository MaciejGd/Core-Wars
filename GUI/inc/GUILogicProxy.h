#pragma once

#include <QtWidgets>
#include <QObject>

#include <functional>

#include "logger.h"

/// Interface between logic of the application and GUI. Its main responsibility
/// is to use signals and slots for communication. Logic will sign for callbacks
/// to react for events accordingly. Will run in another thread so computations 
/// wont block GUI responsivness.
class GUILogicProxy : public QObject {
    using slot_cb = std::function<void()>;    
    using instr_cb = std::function<void(int)>;
    Q_OBJECT
public:
    GUILogicProxy(QObject* parent = nullptr): QObject(parent){};

    // callback setters
    void SetPauseGameCb(slot_cb cb) { m_pause_game_cb = cb; };
    void SetLoadGameCb(slot_cb cb) { m_load_game_cb = cb; };
    void SetRestartGameCb(slot_cb cb) { m_restart_game_cb = cb; };
    void SetStartGameCb(slot_cb cb) { m_start_game_cb = cb; };
    void SetInstrDataCb(instr_cb cb) { m_instruction_data_cb = cb; }

    // signal senders
    void SendPlayerMoveEvent(int cell, int player_id, int modified_cell) { emit SignalPlayerMove(cell, player_id, modified_cell); };
    void SendPlayerLoadEvent(int starting_idx, int instructions_amount, int player_id)  
                            { emit SignalPlayerLoad(starting_idx, instructions_amount, player_id); };
    void SendInstructionData(const std::string& instruction, int cell_idx) { emit SignalInstructionData(QString(instruction.c_str()), cell_idx); };

    void CheckPendingEvents();

private:
    slot_cb m_pause_game_cb;
    slot_cb m_load_game_cb;
    slot_cb m_restart_game_cb;
    slot_cb m_start_game_cb;
    instr_cb m_instruction_data_cb;

public slots:
    void SlotPauseGame();
    void SlotLoadPlayers();
    void SlotRestartGame();
    void SlotStartGame();
    void SlotInstructionData(int cell_idx);

signals:
    void SignalPlayerMove(int cell, int player_id, int modified_cell); // cell to be passed to main menu
    void SignalPlayerLoad(int starting_idx, int instructions_amount, int player_id);
    void SignalInstructionData(QString instruction, int cell_idx);
};