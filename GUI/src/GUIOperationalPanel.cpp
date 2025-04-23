#include "GUIOperationalPanel.h"
#include "logger.h"
#include "GUIUtils.h"

GUIOperationalPanel::GUIOperationalPanel(QWidget* parent): QWidget(parent) 
{
    QVBoxLayout* layout = new QVBoxLayout{this};
    m_players_panel = new GUIPlayersPanel{this};
    m_stacks = new GUIStackPanel{this};
    
    layout->setSpacing(0);
    layout->addWidget(m_players_panel);
    layout->addWidget(m_stacks);
    // debug
    //SetColor(this, QColor("magenta"));
    
}

void GUIOperationalPanel::UpdatePlayersStack(int player_id, const QString &stack_operation, int cell_idx)
{
    if (m_stacks == nullptr)
    {
        LOG_ERR("GUIStacks object is invalid, aborting operation");
        return;
    }
    m_stacks->UpdatePlayerStack(player_id, stack_operation, cell_idx);
}

void GUIOperationalPanel::SetPlayerColor(int player_id, const QString &color)
{
    if (m_stacks == nullptr)
    {
        LOG_ERR("GUIStacks object is invalid, aborting operation");
        return;
    }
    m_stacks->SetPlayerColor(player_id, color);
    m_players_panel->SetPlayerColor(player_id, color);
}

void GUIOperationalPanel::ClearStacks()
{
    if (m_stacks == nullptr)
    {
        LOG_ERR("GUIStacks object is invalid, aborting operation");
        return;
    }
    m_stacks->ClearStacks();
}

bool GUIOperationalPanel::GetPlayersPaths(std::vector<std::string>& paths)
{
    // TODO: insert return statement here
    if (m_players_panel != nullptr) {
        return m_players_panel->GetPlayersPaths(paths);
    }
    return false;

}
