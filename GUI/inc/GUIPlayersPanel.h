#pragma once

#include "GUIPlayerTextField.h"

#include <QtWidgets>

/// @brief Panel built from text fields storing path to players programs
class GUIPlayersPanel : public QWidget {
    Q_OBJECT
public:
    GUIPlayersPanel(QWidget* parent = nullptr);


    /// @brief Get paths to the programs for all players 
    /// @param paths vector to be filled with paths to warriors code
    /// @return true if success, false if some path is missing
    bool GetPlayersPaths(std::vector<std::string>& paths);
private:
    std::vector<GUIPlayerTextField*> m_players;
    // GUIPlayerTextField* m_first_player;
    // GUIPlayerTextField* m_second_player;
};
