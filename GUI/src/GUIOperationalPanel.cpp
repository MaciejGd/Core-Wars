#include "GUIOperationalPanel.h"

GUIOperationalPanel::GUIOperationalPanel(QWidget* parent): QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout{};
    m_players_panel = new GUIPlayersPanel{this};
    
    layout->addWidget(m_players_panel);
    setLayout(layout);
}

