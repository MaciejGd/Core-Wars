#include "GUIConstants.h"

namespace GUI 
{
// possible colors for players, as QStrings
const std::vector<QString> PLAYERS_COLORS = {
    "#5a3e71", // purple
    "#3a86ff", // blue will stay
    "#c70e32", // red
    "#326c3c"  // green
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

// toolbar
const int TOOLBAR_BUTTON_HEIGHT = 20;
const int TOOLBAR_BUTTON_WIDTH  = 90;
const QString MAX_ROUNDS = "8000";

// colors
const QColor DEFAULT_FONT_COLOR =       QColorConstants::Black;
const QColor MAIN_WINDOW_COLOR =        QColorConstants::DarkGray;
const QColor TEXT_FIELD_BACKGROUND =    QColorConstants::LightGray;
const QColor STACK_BACKGROUND_COLOR =   QColorConstants::LightGray;
// const QString ARENA_CELL_DEFAULT_COLOR = "#cac9c9"; // light grey color
const QString ARENA_CELL_DEFAULT_COLOR = "#D3D3D3"; // light grey color

// related to stack
const QString OPERATION_PRINT = "%1: %2";

// cells stylling
const QString CELL_STYLING = "font-weight: bold; color: %1; background-color: %2; border-top: 1px solid  #8e99a2; border-left: 1px solid #8e99a2";

// player path choose
const int PLAYER_PATH_TEXTFIELD_WIDTH = 300;
const int PLAYER_PATH_TEXTFIELD_HEIGHT = 20;

// amount of players playing, 2 by default
int PLAYERS_AMOUNT = 2;
};
