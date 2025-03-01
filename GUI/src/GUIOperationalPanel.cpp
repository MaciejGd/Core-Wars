#include "GUIOperationalPanel.h"

GUIOperationalPanel::GUIOperationalPanel(QWidget* parent): QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout{this};
    m_players_panel = new GUIPlayersPanel{};
    
    layout->addWidget(m_players_panel);
}

