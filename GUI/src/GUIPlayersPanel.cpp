#include "GUIPlayersPanel.h"
#include "GUIUtils.h"


GUIPlayersPanel::GUIPlayersPanel(QWidget* parent): QWidget(parent) 
{
    QVBoxLayout* layout = new QVBoxLayout{this};
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    // by default create two players
    m_players.push_back(new GUIPlayerTextField{" PLAYER 0:",this});
    m_players.push_back(new GUIPlayerTextField{" PLAYER 1:",this});

    layout->addWidget(m_players[0]);
    layout->addWidget(m_players[1]);

    this->setMaximumHeight(this->sizeHint().height());
}

void GUIPlayersPanel::SetPlayerColor(int player_id, const QString& color)
{
    m_players[player_id]->SetColor(color);
}

bool GUIPlayersPanel::GetPlayersPaths(std::vector<std::string>& paths)
{
    // clear vector if it contains any data
    for (int i = 0; i < m_players.size(); i++)
    {
        std::string path = m_players[i]->GetPlayerPath();
        if (path == "")
        {
            return false;
        }
        paths.push_back(path);
    }
    
    return true;
}
