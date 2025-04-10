#include "GUIPlayerStack.h"

GUIPlayerStack::GUIPlayerStack(QWidget *parent): QTextEdit(parent)
{
    setReadOnly(true);
    setTextBackgroundColor(STACK_COLOR);
}

void GUIPlayerStack::Update(QString &stack_operation)
{
    setReadOnly(false);
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::Start);
    cursor.insertText(stack_operation + "\n");
    setReadOnly(true);
}
