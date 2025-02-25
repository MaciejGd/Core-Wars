#include "GUIPlayersPanel.h"



GUIPlayersPanel::GUIPlayersPanel(QWidget* parent): QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout{this};
    m_first_player = new GUIPlayerTextField{this};
    m_second_player = new GUIPlayerTextField{this};
    layout->addWidget(m_first_player);
    layout->addWidget(m_second_player);

    setLayout(layout);
}