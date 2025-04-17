#include "GUIMemoryCell.h"
#include "GUIConstants.h"
#include "GUIUtils.h"
#include "logger.h"

void GUIMemoryCell::SetCellFocused(const QString &player_color)
{
    setText(""); // set empty text
    //m_background_color = player_color;
    // make background color a bit brighter
    QColor player;
    if (player_color != "black")
    {
        player = QColor(player_color);
        player = player.lighter(150);
    }
    else {
        // if color equal to black, lighting with ligter method wont work as desired 
        player = QColor(QColorConstants::DarkGray);
    }
    setStyleSheet(GUI::CELL_STYLING.arg(m_foreground_color, QString(player.name())));
}


void GUIMemoryCell::SetCellModified(const QString &player_color)
{
    m_text = "X";
    this->setText(m_text);
    m_foreground_color = player_color;
    
    setStyleSheet(GUI::CELL_STYLING.arg(m_foreground_color, m_background_color));
    //SetColor(this, QColor(player_color));
}


void GUIMemoryCell::SetCellAsInitial(const QString & player_color)
{
    m_background_color = player_color;
}


void GUIMemoryCell::ClearCell(const QString& color)
{
    m_foreground_color = color;
    m_background_color = color;
    m_text = "";
    this->setText(m_text);
    setStyleSheet(GUI::CELL_STYLING.arg(m_foreground_color, m_background_color));
}


void GUIMemoryCell::RestoreCellStyling()
{
    // we want to set params in this order: foreground, background
    setStyleSheet(GUI::CELL_STYLING.arg(m_foreground_color, m_background_color));
    setText(m_text);
}
