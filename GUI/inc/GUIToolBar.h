#pragma once

#include "QPushButton"
#include "GUIFileExplorerDialog.h"

#include <QToolBar>
#include <QString>
#include <memory>


/// @brief Implementation of functional buttons bar
class GUIToolBar : public QToolBar {
    Q_OBJECT     
public:
    GUIToolBar(const QString& name = "", QWidget* parent = nullptr);

    /// @brief Increase rounds counter shown in label
    void SetCounter(int value);

    QPushButton* GetLoadButton() { return m_load_btn; };
    QPushButton* GetRestartButton() { return m_restart_btn; };
    QPushButton* GetPauseButton() { return m_pause_btn; };
    QPushButton* GetPlayButton() { return m_play_btn; };
    QPushButton* GetSpeedUpButton() { return m_speedup_btn; }; 
    QPushButton* GetSlowDownButton() { return m_slowdown_btn; };

private:
    void m_InitButton(QPushButton*& btn, const QString& title);
    void m_InitSpeedLabel();
    void m_InitRoundsCnt();
    void m_AdjustPlaySpeed(bool speedup);
    // buttons
    QPushButton* m_play_btn;
    QPushButton* m_pause_btn;
    QPushButton* m_load_btn;
    QPushButton* m_restart_btn;
    QPushButton* m_speedup_btn;
    QPushButton* m_slowdown_btn;
    QLabel* m_game_speed;
    QLabel* m_rounds_cnt;
    // string indicating speed of program execution

    QString m_play_speed = "x1.0";
    QString m_rounds_str = "ROUND: %1/%2";

private slots:
    void SlotSpeedUp();
    void SlotSlowDown();

};