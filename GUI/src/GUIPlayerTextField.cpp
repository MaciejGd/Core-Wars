#include "GUIPlayerTextField.h"
#include "logger.h"

#include "GUIUtils.h"
#include "GUIConstants.h"

#include <iostream>


GUIPlayerTextField::GUIPlayerTextField(const QString& player_name, QWidget* parent): QWidget(parent), m_player_path("") 
{
    // responsible for setting text above text field
    QVBoxLayout* layout = new QVBoxLayout{};
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 10);
    layout->setAlignment(Qt::AlignTop);

    m_InitLabel(player_name);
    m_InitTextField();

    m_player_id->setAlignment(Qt::AlignLeft);    

    layout->addWidget(m_player_id, Qt::AlignLeft);
    //outer_layout->addWidget(inner_wgt);
    layout->addWidget(m_textfield);

    setLayout(layout);
}

void GUIPlayerTextField::m_InitLabel(const QString& player_name) 
{
    // initialize label with player name
    m_player_id = new QLabel{};
    m_player_id->setText(player_name);
    m_player_id->setAlignment(Qt::AlignCenter);
    m_player_id->setFixedHeight(TEXT_FIELD_HEIGHT);
}

void GUIPlayerTextField::m_InitTextField()
{
    // initialize textfield
    m_textfield = new GUITextFieldButton(BTN_WIDTH, TEXT_FIELD_HEIGHT, "TEST");
    m_textfield->SetButtonCallback(this, &GUIPlayerTextField::ChoosePlayersCb);
    m_textfield->setFixedHeight(TEXT_FIELD_HEIGHT);
    m_textfield->SetTextfieldWidth(GUI::PLAYER_PATH_TEXTFIELD_WIDTH); 
}

void GUIPlayerTextField::ChoosePlayersCb() 
{
    LOG_DBG("Launching file explorer");
    m_file_explorer = std::make_unique<GUIFileExplorerDialog>(m_textfield->GetText(), this);
    m_file_explorer->show();
    // connect tool bar with file search window (will be moved to another widget)
    connect(m_file_explorer.get(), &GUIFileExplorerDialog::FilePathChanged, 
        this, &GUIPlayerTextField::PlayerPathChangedCb);
}

void GUIPlayerTextField::PlayerPathChangedCb(QString& path) 
{
    LOG_DBG("New path for a player is {}", path.toStdString());
    m_textfield->SetText(path);
    m_player_path = path.toStdString();
}

