#include "GUIMemoryCell.h"
#include "GUIConstants.h"

void GUIMemoryCell::SetCellFocused(const QString &player_color)
{
    m_foreground_color = player_color;
    setStyleSheet(GUI::CELL_STYLING.arg(m_foreground_color, m_background_color));
    setText(""); // set empty text
}

void GUIMemoryCell::SetCellModified(const QString &player_color)
{
    m_text = "X";
    m_foreground_color = player_color;
}

void GUIMemoryCell::SetCellAsInitial(const QString & player_color)
{
    m_background_color = player_color;
}

void GUIMemoryCell::RestoreCellStyling()
{
    // we want to set params in this order: foreground, background
    setStyleSheet(GUI::CELL_STYLING.arg(m_foreground_color, m_background_color));
    setText(m_text);
}
