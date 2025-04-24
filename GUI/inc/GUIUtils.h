#pragma once

#include <QtWidgets>
#include "GUIConstants.h"

/// @brief Set background color of the widget 
/// @param obj pointer to widget we want change background color in
/// @param color new color to be set as background
inline void SetColor(QWidget* obj, const QColor& color)
{
    QPalette pal = obj->palette();
    pal.setColor(QPalette::Window, color);
    obj->setAutoFillBackground(true);
    obj->setPalette(pal);
}

/// @brief Set background color of the textbased widget like QLabel or QTextEdit 
/// @param obj pointer to widget we want change background color in
/// @param color new color to be set as background
inline void SetColorBase(QWidget* obj, const QColor& color)
{
    obj->setAutoFillBackground(true);
    QPalette pal = obj->palette();
    pal.setColor(QPalette::Base, color);
    obj->setPalette(pal);
}

/// @brief Set foreground color of the widget 
/// @param obj pointer to widget we want change foreground color in
/// @param color new color to be set as foreground
inline void SetTextColor(QWidget* obj, const QColor& color = GUI::DEFAULT_FONT_COLOR)
{
    QPalette pal = obj->palette();
    pal.setColor(QPalette::WindowText, color);
    obj->setPalette(pal);
}

/// @brief Set foreground color of the textbased widget like QLabel or QTextEdit 
/// @param obj pointer to widget we want change foreground color in
/// @param color new color to be set as foreground
inline void SetTextColorBase(QWidget* obj, const QColor& color = GUI::DEFAULT_FONT_COLOR)
{
    QPalette pal = obj->palette();
    pal.setColor(QPalette::Text, color);
    obj->setPalette(pal);
}