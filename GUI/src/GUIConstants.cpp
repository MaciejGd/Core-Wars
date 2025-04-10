#include "GUIConstants.h"

namespace GUI 
{
// possible colors for players, as QStrings
const std::vector<QString> PLAYERS_COLORS = {
    "red",
    "green",
    "blue",
    "cyan",
    "magenta",
    "darkyellow"
};
// map of color strings to QColor objects
const std::map<QString, QColor> STR_TO_COL = {
    {"red", QColorConstants::Red},
    {"green", QColorConstants::Green},
    {"blue", QColorConstants::Blue},
    {"cyan", QColorConstants::Cyan},
    {"magenta", QColorConstants::Magenta},
    {"darkyellow", QColorConstants::DarkYellow},
};

// related to arena dimensions
const int CELLS_AMOUNT = 8000;
const int CELL_WIDTH = 10;
const int ARENA_WIDTH  = 1000;
const int ARENA_HEIGHT = 800;

// instruction dialog related
const QString INSTRUCTION_DIALOG_TITLE = "Instruction at %1";
const int INSTRUCTION_DIALOG_WIDTH = 200;
const int INSTRUCTION_DIALOG_HEIGHT = 50;

// related to stack
const QColor STACK_BACKGROUND_COLOR = QColorConstants::Gray;
const QString OPERATION_PRINT = "%1: %2";

};