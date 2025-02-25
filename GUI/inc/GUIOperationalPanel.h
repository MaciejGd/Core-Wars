#pragma once

#include <QtWidgets>
#include "GUIPlayersPanel.h"
 
/// @brief Wrapper for whole left panel of the application
class GUIOperationalPanel : public QWidget {
    Q_OBJECT
public:
    GUIOperationalPanel(QWidget* parent = nullptr);

private: 
    GUIPlayersPanel* m_players_panel;

};