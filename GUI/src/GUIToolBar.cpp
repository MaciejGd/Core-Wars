#include "GUIToolBar.h"
#include <iostream>

GUIToolBar::GUIToolBar(const QString& name, QWidget* parent) : QToolBar(name, parent) {
    m_choose_first_btn = new QPushButton("CHOOSE_FIRST_FIGHTER");
    m_choose_second_btn = new QPushButton("CHOOSE_SECOND_FIGHTER");
    m_reset_btn = new QPushButton("RESET_ARENA");

    connect(m_choose_first_btn, &QPushButton::pressed, this, &GUIToolBar::ChoosePlayersCb);
    connect(m_choose_second_btn, &QPushButton::pressed, this, &GUIToolBar::ChoosePlayersCb);

    addWidget(m_choose_first_btn);
    addWidget(m_choose_second_btn);
    addWidget(m_reset_btn);
}

// slots
void GUIToolBar::ResetButtonCb() {
    std::cout << "ResetButtonCb\n";
}

void GUIToolBar::ChoosePlayersCb() {
    //m_choose_btn
    std::cout << "Players choose callback\n";
    m_file_explorer = std::make_unique<GUIFileExplorer>();
    m_file_explorer->show();
    // connect tool bar with file search window (will be moved to another widget)
    connect(m_file_explorer.get(), &GUIFileExplorer::FilePathChanged, this, &GUIToolBar::PlayerPathChangedCb);
}
// this will be removed from here and place in separate widget, with read-only textfield
void GUIToolBar::PlayerPathChangedCb(QString& path) {
    // dummy implementation
    std::cout << "File path is: " << path.toStdString() << std::endl;
}