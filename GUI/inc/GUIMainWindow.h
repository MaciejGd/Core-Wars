#pragma once

#include <QtWidgets>
#include "GUIArena.h"
#include "GUIToolBar.h"
#include "GUIOperationalPanel.h"
#include "GUILogicProxy.h"

#include <iostream> // DEBUG

/// Main window of the application
/// Consists of three main elements:
/// - Functional buttons
/// - Arena
/// - Stats panel
class GUIMainWindow : public QMainWindow {
    Q_OBJECT
public:
    GUIMainWindow(int width, int height, GUILogicProxy& logic_proxy, QWidget* parent = nullptr);

    /// @brief Show player's move in GUI
    /// @param cell memory cell to be modified
    /// @param player_id player moving
    /// @return boolean indicating status of operation
    bool MakePlayerMove(int cell, int player_id, int modified_cell);    
    
    void m_ConnectWorkerThread(QThread* thread);
private:
    GUILogicProxy& m_logic_proxy;
    // widget for arena
    GUIArena* m_arena;
    // widget for functional buttons
    GUIToolBar* m_toolBar;
    // widget for stats panel
    GUIOperationalPanel* m_op_panel;

    /// @brief Connect proxy with main window widget using slots 
    void m_ConnectProxy();

    /// @brief Connect toolbar buttons two proper GUILogic proxy slots
    void m_ConnectButtons();

    void m_ConnectArena();

    

private slots:
    void SlotPlayerLoaded(int starting_idx, int instructions_amount, int player_id);
    void SlotPlayerMove(int cell, int player_id, int modified_cell);
signals:
    void SignalLoadPlayers();

};
