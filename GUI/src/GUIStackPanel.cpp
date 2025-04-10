#include "GUIStackPanel.h"
#include "GUIConstants.h"
#include "logger.h"

GUIStackPanel::GUIStackPanel(QWidget *parent): QWidget(parent)
{
    // create two players stack by default
    GUIPlayerStack* player1 = new GUIPlayerStack{this};
    GUIPlayerStack* player2 = new GUIPlayerStack{this};

    QHBoxLayout* layout = new QHBoxLayout{this};
    layout->addWidget(player1);
    layout->addWidget(player2);
    
    m_player_stacks.clear();
    m_player_stacks.push_back(player1);
    m_player_stacks.push_back(player2);
}

void GUIStackPanel::SetPlayerColor(int player_id, const QString& color)
{
    if (player_id < 0 || player_id >= m_player_stacks.size())
    {
        LOG_ERR("Wrong player id: {} has been passed", player_id);
        return;
    }
    if (m_player_stacks[player_id] == nullptr)
    {
        LOG_ERR("Player stack: {} is invalid", player_id);
        return;
    }
    LOG_DBG("Setting color for player stack");
    m_player_stacks[player_id]->SetTextColor(color);
}

void GUIStackPanel::ClearStacks()
{
    for (auto& stack : m_player_stacks)
    {
        stack->clear();
    }
}

void GUIStackPanel::UpdatePlayerStack(int player_id, const QString& stack_operation, int cell_idx)
{
    if (player_id < 0 || player_id >= m_player_stacks.size())
    {
        LOG_ERR("Wrong player id: {} has been passed", player_id);
        return;
    }
    if (m_player_stacks[player_id] == nullptr)
    {
        LOG_ERR("Player stack: {} is invalid", player_id);
        return;
    }
    m_player_stacks[player_id]->Update(stack_operation, cell_idx);
}