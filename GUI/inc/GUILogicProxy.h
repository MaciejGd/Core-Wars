#pragma once

#include <QtWidgets>
#include <QObject>

#include <functional>
#include <vector>
#include <string>

#include "logger.h"

/// Interface between logic of the application and GUI. Its main responsibility
/// is to use signals and slots for communication. Logic will sign for callbacks
/// to react for events accordingly. Will run in another thread so computations 
/// wont block GUI responsivness.
class GUILogicProxy : public QObject {
    using slot_cb = std::function<void()>;    
    using instr_cb = std::function<void(int)>;
    using load_cb = std::function<void(const std::vector<std::string>&)>;
    Q_OBJECT
public:
    GUILogicProxy(QObject* parent = nullptr): QObject(parent){};

    // callback setters
    inline void SetPauseGameCb(slot_cb cb) { m_pause_game_cb = cb; };
    inline void SetRestartGameCb(slot_cb cb) { m_restart_game_cb = cb; };
    inline void SetStartGameCb(slot_cb cb) { m_start_game_cb = cb; };
    inline void SetSpeedUpGameCb(slot_cb cb) { m_speedup_game_cb = cb; };
    inline void SetSlowDownGameCb(slot_cb cb) { m_slowdown_game_cb = cb; };
    inline void SetLoadGameCb(load_cb cb) { m_load_game_cb = cb; };
    inline void SetInstrDataCb(instr_cb cb) { m_instruction_data_cb = cb; }

    // signal senders
    inline void SendCounter(int round_counter) 
                            { emit SignalChangeCounter(round_counter); };

    inline void SendPlayerMoveEvent(int cell, int player_id, int modified_cell, const std::string& instruction) 
                            { emit SignalPlayerMove(cell, player_id, modified_cell, QString(instruction.c_str())); };

    inline void SendPlayerLoadEvent(int starting_idx, int instructions_amount, int player_id, int offset)  
                            { emit SignalPlayerLoad(starting_idx, instructions_amount, player_id, offset); };

    inline void SendInstructionData(const std::string& instruction, int cell_idx) 
                            { emit SignalInstructionData(QString(instruction.c_str()), cell_idx); };

    inline void SendShowInfoDialog(const std::string& msg, bool critical = false) 
                            { emit SignalShowInfoDialog(QString(msg.c_str()), critical); };

    /// @brief Poll events awaiting in queue
    void CheckPendingEvents();

private:
    slot_cb m_pause_game_cb;
    slot_cb m_restart_game_cb;
    slot_cb m_start_game_cb;
    slot_cb m_speedup_game_cb;
    slot_cb m_slowdown_game_cb;
    load_cb m_load_game_cb;
    instr_cb m_instruction_data_cb;

public slots:
    void SlotLoadPlayers(const std::vector<std::string>& paths);
    void SlotInstructionData(int cell_idx);
    void SlotPauseGame();
    void SlotRestartGame();
    void SlotStartGame();
    void SlotSpeedUpGame();
    void SlotSlowDownGame();

signals:
    void SignalChangeCounter(int round_counter);
    void SignalPlayerMove(int cell, int player_id, int modified_cell, QString instruction); // cell to be passed to main menu
    void SignalPlayerLoad(int starting_idx, int instructions_amount, int player_id, int offset);
    void SignalInstructionData(QString instruction, int cell_idx);
    void SignalShowInfoDialog(const QString& msg, bool critical);
};