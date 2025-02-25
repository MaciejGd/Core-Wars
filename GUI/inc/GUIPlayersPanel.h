#pragma once

#include "GUIPlayerTextField.h"

#include <QtWidgets>

/// @brief Panel built from text fields storing path to players programs
class GUIPlayersPanel : public QWidget {
    Q_OBJECT
public:
    GUIPlayersPanel(QWidget* parent = nullptr);
private:
    GUIPlayerTextField* m_first_player;
    GUIPlayerTextField* m_second_player;
};
