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

private:
    // buttons
    QPushButton* m_play_btn;
    QPushButton* m_stop_btn;
    QPushButton* m_reset_btn;
    QPushButton* m_speedup_btn;

};