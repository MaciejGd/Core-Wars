#include "GUIPlayersPanel.h"



GUIPlayersPanel::GUIPlayersPanel(QWidget* parent): QWidget(parent) 
{
    QVBoxLayout* layout = new QVBoxLayout{this};
    // by default create two players
    m_players.push_back(new GUIPlayerTextField{"",this});
    m_players.push_back(new GUIPlayerTextField{"",this});
    // m_first_player = new GUIPlayerTextField{};
    // m_second_player = new GUIPlayerTextField{};
    layout->addWidget(m_players[0]);
    layout->addWidget(m_players[1]);
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
