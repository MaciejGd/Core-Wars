#include "GUIPlayerStack.h"
#include "GUIConstants.h"

GUIPlayerStack::GUIPlayerStack(QWidget *parent): QTextEdit(parent)
{
    setReadOnly(true);
    // change background of stack
    QPalette p = this->palette();
    p.setColor(QPalette::Base, GUI::STACK_BACKGROUND_COLOR); 
    this->setPalette(p);
}

void GUIPlayerStack::Update(const QString &stack_operation, int cell_idx)
{
    this->setReadOnly(false);
    // insert new operation at the top of panel
    QString stack_str = m_PrepareStackPrint(stack_operation, cell_idx);
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::Start);
    cursor.insertText(stack_str + "\n", m_format);
    this->setReadOnly(true);
}


void GUIPlayerStack::SetTextColor(const QString& color)
{
    m_format.setForeground(QColor(color));
}

QString GUIPlayerStack::m_PrepareStackPrint(const QString& operation, int cell_idx)
{
    // ensure always 4 digits will be printed
    QString cell_str = QString::number(cell_idx);
    QString spacing = QString(4 - cell_str.size(), '0');

    return GUI::OPERATION_PRINT.arg(cell_str, operation);
}