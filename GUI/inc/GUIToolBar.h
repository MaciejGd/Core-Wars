#pragma once

#include "QPushButton"
#include "GUIFileExplorer.h"

#include <QToolBar>
#include <QString>
#include <memory>


class GUIToolBar : public QToolBar {
    Q_OBJECT 
    QPushButton* m_choose_first_btn;
    QPushButton* m_choose_second_btn;
    QPushButton* m_reset_btn;
    std::unique_ptr<GUIFileExplorer> m_file_explorer;
public:
    GUIToolBar(const QString& name = "", QWidget* parent = nullptr);
    void ResetButtonCb();

private slots:
    void ChoosePlayersCb();
    void PlayerPathChangedCb(QString& path);
};