#include "GUIInstructionDialog.h"
#include "GUIConstants.h"

GUIInstructionDialog::GUIInstructionDialog(const QString &instruction_string, int cell_idx, QWidget *parent):
    QDialog(parent)
{
    // customize window title to consist index of memory cell 
    setWindowTitle(GUI::INSTRUCTION_DIALOG_TITLE.arg(QString(QString::number(cell_idx))));
    //setWindowTitle(" ");
    resize(GUI::INSTRUCTION_DIALOG_WIDTH, GUI::INSTRUCTION_DIALOG_HEIGHT);    

    m_instruction = new QLabel(this);
    m_instruction->setText(instruction_string);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_instruction);
}
