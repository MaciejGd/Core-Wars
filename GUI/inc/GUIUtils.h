#pragma once

#include <QtWidgets>
#include "GUIConstants.h"

inline void SetColor(QWidget* obj, const QColor& color)
{
    QPalette pal = obj->palette();
    pal.setColor(QPalette::Window, color);
    obj->setAutoFillBackground(true);
    obj->setPalette(pal);
}

inline void SetTextColor(QWidget* obj, const QColor& color = GUI::DEFAULT_FONT_COLOR)
{
    QPalette pal = obj->palette();
    pal.setColor(QPalette::WindowText, color);
    obj->setPalette(pal);
}