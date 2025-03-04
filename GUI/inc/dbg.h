#pragma once

#include <QtWidgets>


/// @brief Set background color of the widget, for debug purposes
/// @param wgt pointer to the widget we want to change 
/// @param color color of the background we want to set
void setColor(QWidget* wgt, QColor color) 
{
    QPalette pal = wgt->palette();
    pal.setColor(QPalette::Window, color);
    wgt->setAutoFillBackground(true);
    wgt->setPalette(pal);
}