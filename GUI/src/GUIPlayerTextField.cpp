#include "GUIPlayerTextField.h"
#include <iostream>


GUIPlayerTextField::GUIPlayerTextField(QWidget* parent): QWidget(parent), m_player_path("") {
    QHBoxLayout* layout = new QHBoxLayout{this};
    m_btn = new QPushButton{this};
    m_btn->setFixedSize(BTN_WIDTH, TEXT_FIELD_HEIGHT);
    m_textfield = new QTextEdit{QString{m_player_path.c_str()}, this};
    m_textfield->setFixedHeight(TEXT_FIELD_HEIGHT);
    m_textfield->setReadOnly(true); // initially set it to true
    
    layout->addWidget(m_textfield);
    layout->addWidget(m_btn);
    
    connect(m_btn, &QPushButton::pressed, this, &GUIPlayerTextField::ChoosePlayersCb);
    setLayout(layout);
}


void GUIPlayerTextField::ChoosePlayersCb() {
    m_file_explorer = std::make_unique<GUIFileExplorer>(this);
    m_file_explorer->show();
    // connect tool bar with file search window (will be moved to another widget)
    connect(m_file_explorer.get(), &GUIFileExplorer::FilePathChanged, 
        this, &GUIPlayerTextField::PlayerPathChangedCb);
}

void GUIPlayerTextField::PlayerPathChangedCb(QString& path) {
    std::cout << "New path for a player is: " << path.toStdString() << std::endl;
    // update text field
    m_textfield->setReadOnly(false);
    m_textfield->setPlainText(path);
    m_textfield->setReadOnly(true);
    m_player_path = path.toStdString();
}

