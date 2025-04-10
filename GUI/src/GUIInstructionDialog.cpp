#include "GUIInstructionDialog.h"


extern const QString INSTRUCTION_DIALOG_TITLE = "Instruction at %1";
extern const int INSTRUCTION_DIALOG_WIDTH = 200;
extern const int INSTRUCTION_DIALOG_HEIGHT = 50;

GUIInstructionDialog::GUIInstructionDialog(const QString &instruction_string, int cell_idx, QWidget *parent):
    QDialog(parent)
{
    // customize window title to consist index of memory cell 
    setWindowTitle(INSTRUCTION_DIALOG_TITLE.arg(QString(QString::number(cell_idx))));
    resize(INSTRUCTION_DIALOG_WIDTH, INSTRUCTION_DIALOG_HEIGHT);    

    m_instruction = new QLabel(this);
    m_instruction->setText(instruction_string);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_instruction);
}
