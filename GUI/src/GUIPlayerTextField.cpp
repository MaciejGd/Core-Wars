#include "GUIPlayerTextField.h"
#include <iostream>

#include "dbg.h" // debug purposes


GUIPlayerTextField::GUIPlayerTextField(const QString& player_name, QWidget* parent): QWidget(parent), m_player_path("") {
    // responsible for setting text above text field
    QVBoxLayout* outer_layout = new QVBoxLayout{};
    outer_layout->setSpacing(0);
    outer_layout->setContentsMargins(0, 0, 0, 0);
    outer_layout->setAlignment(Qt::AlignTop);
    // resonsible for setting button next to textfield
    // QWidget* inner_wgt = new QWidget{};
    // inner_wgt->setFixedHeight(TEXT_FIELD_HEIGHT);
    // QHBoxLayout* inner_layout = new QHBoxLayout{inner_wgt};
    // m_btn = new QPushButton{};
    // m_btn->setFixedSize(BTN_WIDTH, TEXT_FIELD_HEIGHT);
    // m_btn->setText("TEST");
    m_textfield = new GUITextFieldButton(TEXT_FIELD_HEIGHT, BTN_WIDTH, "TEST");
    // m_InitTextField();
    m_InitLabel(player_name);

    // inner horizontal layout for text field and button
    // inner_layout->addWidget(m_textfield);
    // inner_layout->addWidget(m_btn);
    // inner_layout->setSpacing(0);
    // inner_layout->setContentsMargins(0,0,0,0);
    // added for testing
    //inner_wgt->setLayout(inner_layout);

    //connect(m_btn, &QPushButton::pressed, this, &GUIPlayerTextField::ChoosePlayersCb);
    m_textfield->SetButtonCallback(this, &GUIPlayerTextField::ChoosePlayersCb);
    // for testing adding QLabel


    outer_layout->addWidget(m_player_id);
    //outer_layout->addWidget(inner_wgt);
    outer_layout->addWidget(m_textfield);

    setLayout(outer_layout);
}

// void GUIPlayerTextField::m_InitTextField() {
//     m_textfield = new QTextEdit{QString{m_player_path.c_str()}};
//     m_textfield->setFixedHeight(TEXT_FIELD_HEIGHT);
//     m_textfield->setReadOnly(true);
// }

void GUIPlayerTextField::m_InitLabel(const QString& player_name) {
    m_player_id = new QLabel{};
    m_player_id->setText("Player's name");
    m_player_id->setAlignment(Qt::AlignCenter);
    m_player_id->setFixedHeight(TEXT_FIELD_HEIGHT);
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
    // m_textfield->setReadOnly(false);
    // m_textfield->setPlainText(path);
    // m_textfield->setReadOnly(true);
    m_textfield->SetText(path);
    m_player_path = path.toStdString();
}

