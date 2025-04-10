#pragma once

#include <QtWidgets>
#include <vector>
#include <map>
#include <string>
#include <memory>

#include "GUIInstructionDialog.h"



/// Widget representing arena that the players will fight on.
/// By default consist of 8000 cells that change color basing on 
/// player executing operation in a cell. 
class GUIArena : public QWidget {
    Q_OBJECT
public:
    GUIArena(int rows, int cols, QWidget *parent = nullptr);
    
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
    /// @return boolean indicating result of operations
    void LoadPlayerCode(int starting_idx, int instructions_amount, int player_id);

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
    std::vector<QLabel*> m_cells;

    /// Function to set color of wanted cell
    void m_SetCellColor(QLabel* cell, const QString& color);

    /// Function used to draw color for a player from the list of colors
    void m_GeneratePlayerColor(int player_id);

    /// To be initialized when player's handle will be passed
    std::map<int, QString> m_players_colors;


    /* static members */
    inline static const QString s_def_color = "white";

    // by default we want to leave lightgrey border of width 1px on the cell
    // std::format will be used later to fill with desired color
    inline static QString s_def_cell_style = "background-color: %1; border: 1px solid lightGrey";

public slots:
    // clear arena when restart press button has been pressed
    void SlotRestartGame();

signals:
    void SignalRequestInstructionData(int cell_idx);
};
