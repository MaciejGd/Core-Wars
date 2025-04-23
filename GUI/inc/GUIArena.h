#pragma once

#include <QtWidgets>
#include <vector>
#include <map>
#include <string>
#include <memory>

#include "GUIInstructionDialog.h"
#include "GUIMemoryCell.h"

/// Widget representing arena that the players will fight on.
/// By default consist of 8000 cells that change color basing on 
/// player executing operation in a cell. 
class GUIArena : public QWidget {
    Q_OBJECT
public:
    GUIArena(int rows, int cols, QWidget *parent = nullptr);
    
    /// @brief Override of eventFilter which helps capturinf events sent to Arena cells
    /// @param obj pressed Arena cell
    /// @param event evemt captured
    /// @return boolean indicating if event should be passed further
    bool eventFilter(QObject* obj, QEvent* event) override;

    /// @brief Clear colors of all cells in arena to default value
    void ClearArena();

    
    /// @brief Color desired cell with player's color
    /// @param cell number of cell to be colored
    /// @param player_id id number of player that is making a move
    /// @return boolean indicating result of operations
    void MakePlayerMove(int cell, int player_id, int modified_cell);

    /// @brief Show initial loaded by player code, by coloring respective cells
    /// @param starting_idx starting index of loaded players code
    /// @param instructions_amount amount of instructions to be loaded to Core
    /// @param player_id id number of player that is making a move
    /// @param offset offset of the program counter in relation to first instruction
    /// @return boolean indicating result of operations
    void LoadPlayerCode(int starting_idx, int instructions_amount, int player_id, int offset);

    /// @brief Return reference to player's color
    /// @param player_id id of player to get color from
    /// @return color of the player at player_id
    const QString& GetPlayerColorString(int player_id) const;

private:
    // number of rows of the arena
    int m_rows;
    // number of cols of the arena
    int m_cols;
    // vector storing cells 
    std::vector<GUIMemoryCell*> m_cells;

    /// Function to set color of wanted cell
    void m_SetCellColor(QLabel* cell, const QString& color);

    /// Function used to draw color for a player from the list of colors
    void m_GeneratePlayerColor(int player_id);

    /// To be initialized when player's handle will be passed
    std::map<int, QString> m_players_colors;

    // map player id to player's head (actual player position)
    std::map<int, int> m_players_heads;
signals:
    void SignalRequestInstructionData(int cell_idx);
};
