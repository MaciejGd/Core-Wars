#pragma once

#include <QtWidgets>



class GUIInstructionDialog : public QDialog {
    Q_OBJECT
public:
    GUIInstructionDialog(const QString& intruction_string, int cell_idx, QWidget* parent = nullptr);

private:
    QLabel* m_instruction;
};