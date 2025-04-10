#pragma once

#include <QtWidgets>

extern const QString INSTRUCTION_DIALOG_TITLE;
extern const int INSTRUCTION_DIALOG_WIDTH;
extern const int INSTRUCTION_DIALOG_HEIGHT;

class GUIInstructionDialog : public QDialog {
    Q_OBJECT
public:
    GUIInstructionDialog(const QString& intruction_string, int cell_idx, QWidget* parent = nullptr);

private:
    QLabel* m_instruction;
};