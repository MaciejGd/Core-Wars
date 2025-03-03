#pragma once

#include <QtWidgets>
#include "GUIPlayersPanel.h"
 
/// @brief Widget for storing stats of the game
///
/// Contains two widgets:
///
///     - players textfields
///
///     - stack for currently executed operations
///
class GUIOperationalPanel : public QWidget {
    Q_OBJECT
public:
    GUIOperationalPanel(QWidget* parent = nullptr);

private: 
    // widget containing path to players code (textfields) 
    GUIPlayersPanel* m_players_panel;
    
    // TODO - add stack widget
};