#pragma once

#include "QPushButton"
#include "GUIFileExplorer.h"

#include <QToolBar>
#include <QString>
#include <memory>


/// @brief Implementation of functional buttons bar
class GUIToolBar : public QToolBar {
    Q_OBJECT     
public:
    GUIToolBar(const QString& name = "", QWidget* parent = nullptr);

    QPushButton* GetLoadButton() { return m_load_btn; };
    QPushButton* GetResetButton() { return m_reset_btn; };
    QPushButton* GetPauseButton() { return m_pause_btn; };
    QPushButton* GetPlayButton() { return m_play_btn; };

private:
    // buttons
    QPushButton* m_play_btn;
    QPushButton* m_pause_btn;
    QPushButton* m_load_btn;
    QPushButton* m_reset_btn;
    QPushButton* m_speedup_btn;
    
};