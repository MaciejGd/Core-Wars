#pragma once

#include <QtWidgets>
#include "GUIPlayersPanel.h"
#include "GUIStackPanel.h"
 
/// Widget for storing stats of the game
/// Contains two widgets:
///     - players textfields
///     - stack for currently executed operations
class GUIOperationalPanel : public QWidget {
    Q_OBJECT
public:
    GUIOperationalPanel(QWidget* parent = nullptr);

    /// @brief Call Update{layersStack on GUIStackPanel object
    /// @param player_id id of the player stack to be modified
    /// @param stack_operation operation to be added to stack
    void UpdatePlayersStack(int player_id, const QString& stack_operation, int cell_idx);

    /// @brief Call SetPlayerColor on GUIStackPanel object
    /// @param player_id id of the player to be modfied
    /// @param color color to be set
    void SetPlayerColor(int player_id, const QString& color);

    /// @brief Clear all stacks
    void ClearStacks();

    bool GetPlayersPaths(std::vector<std::string>& paths); 
private: 
    // widget containing path to players code (textfields) 
    GUIPlayersPanel* m_players_panel;

    GUIStackPanel* m_stacks;
    
    // TODO - add stack widget
};