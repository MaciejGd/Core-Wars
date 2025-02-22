#pragma once

#include <QtWidgets>


class GuiField : public QWidget {
    Q_OBJECT
public:
    GuiField(int rows, int cols, QWidget *parent = nullptr);
};
