#pragma once

#include <QtWidgets>



/// Widget representing dialog that shows instruction currently stored at
/// memory cell specified by index
class GUIInstructionDialog : public QDialog {
    Q_OBJECT
public:
    GUIInstructionDialog(const QString& intruction_string, int cell_idx, QWidget* parent = nullptr);

private:
    QLabel* m_instruction;
};