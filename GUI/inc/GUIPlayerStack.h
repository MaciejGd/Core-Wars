#pragma once 

#include <QtWidgets>

/// @brief Widget for displaying currently executed operations
class GUIPlayerStack : public QTextEdit {
    Q_OBJECT
public:
    GUIPlayerStack(QWidget* parent = nullptr);

    /// @brief Add new operation to players stack
    /// @param stack_operation operation to be added to stack
    void Update(const QString& stack_operation, int cell_idx);


    void SetTextColor(const QString& color);

private:
    // needed to change text color
    QTextCharFormat m_format; 

    QString m_PrepareStackPrint(const QString& operation, int cell_idx);
};