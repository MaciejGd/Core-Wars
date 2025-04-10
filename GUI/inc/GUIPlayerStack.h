#pragma once 

#include <QtWidgets>

const QColor STACK_COLOR = QColorConstants::Gray;

/// @brief Widget for displaying currently executed operations
class GUIPlayerStack : public QTextEdit {
    Q_OBJECT
public:
    GUIPlayerStack(QWidget* parent = nullptr);

    /// @brief Add new operation to players stack
    /// @param stack_operation operation to be added to stack
    void Update(QString& stack_operation);


};