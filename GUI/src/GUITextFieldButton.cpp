#include "GUITextFieldButton.h"
#include "GUIUtils.h"

GUITextFieldButton::GUITextFieldButton(int btn_width, int height, const QString& btn_txt, QWidget* parent): 
    QWidget(parent), m_height(height), m_btn_txt(btn_txt), m_btn_width(btn_width) 
{
    QHBoxLayout* layout = new QHBoxLayout{this};
    layout->setSpacing(0);

    m_InitButton();
    m_InitTextField();

    // DEBUG

    layout->addWidget(m_textfield);
    layout->addWidget(m_btn);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
}

void GUITextFieldButton::SetReadOnly(bool read_only) 
{
    m_textfield->setReadOnly(read_only);
}

void GUITextFieldButton::SetText(const QString& text) 
{
    m_textfield->setText(text);
}

const QString GUITextFieldButton::GetText() const 
{
    return m_textfield->toPlainText();
}

void GUITextFieldButton::SetTextfieldWidth(int width)
{
    m_textfield->setFixedWidth(width);
}

void GUITextFieldButton::SetTextfieldHeight(int height)
{
    m_textfield->setFixedHeight(height);
}

void GUITextFieldButton::m_InitButton() 
{
    m_btn = new QPushButton{};
    m_btn->setFixedSize(m_btn_width, m_height);
    m_btn->setText(m_btn_txt);
}

void GUITextFieldButton::m_InitTextField() 
{
    m_textfield = new QTextEdit(QString{m_player_path.c_str()});
    m_textfield->setFixedHeight(m_height);
    m_textfield->setReadOnly(true);
    SetColorBase(m_textfield, GUI::TEXT_FIELD_BACKGROUND);
    SetTextColorBase(m_textfield, QColorConstants::Black);
}
