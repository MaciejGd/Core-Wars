#pragma once

#include "QPushButton"
#include "GUIFileExplorer.h"

#include <QToolBar>
#include <QString>
#include <memory>


class GUIToolBar : public QToolBar {
    Q_OBJECT 
    QPushButton* m_play_btn;
    QPushButton* m_stop_btn;
    QPushButton* m_reset_btn;
    QPushButton* m_speedup_btn;
    std::unique_ptr<GUIFileExplorer> m_file_explorer;
public:
    GUIToolBar(const QString& name = "", QWidget* parent = nullptr);
    void ResetButtonCb();

private slots:
    void ChoosePlayersCb();
    void PlayerPathChangedCb(QString& path);
};