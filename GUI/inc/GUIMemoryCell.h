#pragma once

#include <QtWidgets>

#include "GUIConstants.h"

class GUIMemoryCell : public QLabel {
public:
    GUIMemoryCell(QWidget* parent=nullptr):QLabel(parent), m_background_color("white"),
                                        m_foreground_color("white"), m_text("") 
    {
        setAutoFillBackground(true);
        setFrameStyle(QFrame::Panel | QFrame::Sunken);
        setAlignment(Qt::AlignCenter);
    };
    
    /// @brief set background color
    /// @param color string representing color to be set as background of the cell
    void SetBackgroundColor(const QString& color) { m_background_color = color;
        setStyleSheet(GUI::CELL_STYLING.arg(m_foreground_color, m_background_color));
    };

    /// @brief set foreground color
    /// @param color string representing color to be set as foreground of the cell
    void SetForegroundColor(const QString& color) { m_foreground_color = color; 
        setStyleSheet(GUI::CELL_STYLING.arg(m_foreground_color, m_background_color));
    };

    /// @brief Clear cell's text and set default color
    /// @param color color to be set as foreground and background of cell
    void ClearCell(const QString& color);

    /// @brief set Text of QLabel
    /// @param text text to be set in the label 
    void SetText(const QString& text) { m_text = text; };
    
    void SetCellFocused(const QString& player_color);

    void SetCellModified(const QString& player_color);

    void SetCellAsInitial(const QString& player_color);

    void RestoreCellStyling();

private:
    QString m_background_color;
    QString m_foreground_color;
    QString m_text;
};