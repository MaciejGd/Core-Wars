#pragma once

#include <QtWidgets>


void setColor(QWidget* wgt, QColor color) {
    QPalette pal = wgt->palette();
    pal.setColor(QPalette::Window, color);
    wgt->setAutoFillBackground(true);
    wgt->setPalette(pal);
}