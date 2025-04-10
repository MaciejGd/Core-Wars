#pragma once

#include <QtWidgets>
#include "GUIPlayerStack.h"

/// GUI element responsible for managing stacks for active players
class GUIStackPanel : public QWidget {
public:
    GUIStackPanel(QWidget* parent = nullptr);

    /// @brief Update stack at player_id
    /// @param player_id id of stack to be modified
    /// @param stack_operation operation to be added to stack
    void UpdatePlayerStack(int player_id, const QString& stack_operation, int cell_idx);

    /// @brief Set color for a player stack
    /// @param player_id id of a player, which color should be changed
    /// @param color color to be set
    void SetPlayerColor(int player_id, const QString& color);

    /// @brief Clear all players stacks
    void ClearStacks();

private:
    std::vector<GUIPlayerStack*> m_player_stacks;
};