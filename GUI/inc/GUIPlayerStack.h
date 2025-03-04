#pragma once 

#include <QtWidgets>


/// @brief Widget for displaying currently executed operations
class GUIPlayerStack : public QTextEdit {
    Q_OBJECT
public:
    GUIPlayerStack(QWidget* parent = nullptr);
private:
};