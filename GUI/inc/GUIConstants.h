#pragma once

#include <QtWidgets>
#include <map>
#include <vector>

namespace GUI 
{

extern const std::vector<QString> PLAYERS_COLORS;
/// @brief map of strings to colors, used in GUI
extern const std::map<QString, QColor> STR_TO_COL;
// related to arena dimensions
extern const int CELLS_AMOUNT;
extern const int CELL_WIDTH;
extern const int ARENA_WIDTH ;
extern const int ARENA_HEIGHT;

// instruction dialog related
extern const QString INSTRUCTION_DIALOG_TITLE;
extern const int INSTRUCTION_DIALOG_WIDTH;
extern const int INSTRUCTION_DIALOG_HEIGHT;
// related to stack

extern const QString OPERATION_PRINT;
// cells styling 
extern const QString CELL_STYLING;
// colors
extern const QColor DEFAULT_FONT_COLOR;
extern const QColor MAIN_WINDOW_COLOR;
extern const QColor TEXT_FIELD_BACKGROUND;
extern const QColor STACK_BACKGROUND_COLOR;
extern const QString ARENA_CELL_DEFAULT_COLOR;



};