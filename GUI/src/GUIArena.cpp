#include "GUIArena.h"
#include "GUIConstants.h"
#include "qpalette.h"
#include "logger.h"

#include <algorithm>
#include <random>


GUIArena::GUIArena(int rows, int cols, QWidget *parent) : m_rows(rows), m_cols(cols), QWidget(parent) 
{
    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            GUIMemoryCell *cell = new GUIMemoryCell{this};
            cell->setFixedSize(GUI::CELL_WIDTH, GUI::CELL_WIDTH);  // Set size of each grid cell
            // set white cell with lightgrey border as default
            cell->SetBackgroundColor(GUI::ARENA_CELL_DEFAULT_COLOR);
            cell->SetForegroundColor(GUI::ARENA_CELL_DEFAULT_COLOR);
            cell->setProperty("idx", i*cols + j);

            cell->installEventFilter(this);
            // add cells to the vector so we can later access it
            m_cells.push_back(cell);

            layout->addWidget(cell, i, j);
        }
    }
    setFixedSize(GUI::ARENA_WIDTH, GUI::ARENA_HEIGHT);
    setLayout(layout);
}


bool GUIArena::eventFilter(QObject* obj, QEvent* event) 
{
    // for testing purposes
    if (event->type() == QEvent::MouseButtonPress) 
    {
        QLabel* cell = qobject_cast<QLabel*>(obj);
        QMouseEvent* mouse_ev = static_cast<QMouseEvent*>(event);
        if (cell == nullptr) return false;
        if (mouse_ev->button() == Qt::RightButton) 
        {
            // show info about cell with dialog
            int cell_idx = cell->property("idx").toInt();
            LOG_WRN("Send signal requesting instruction at cell {}", cell_idx);
            emit SignalRequestInstructionData(cell_idx);
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}


void GUIArena::ClearArena()
{
    for (int i = 0; i < m_cells.size(); i++)
    {
        m_cells[i]->ClearCell(GUI::ARENA_CELL_DEFAULT_COLOR);
    }
}

 
void GUIArena::MakePlayerMove(int cell, int player_id, int modified_cell)
{
    // cell out of bounds
    if (cell > (GUI::CELLS_AMOUNT - 1) || cell < 0)
    {
        LOG_ERR("Cell {}, outside of Arena!", cell);
        return;
    }
    // player id not existing
    if (m_players_colors.find(player_id) == m_players_colors.end())
    {   
        LOG_ERR("No player with id {}, has been created from the GUI perspective!");
        return;
    }
    QString player_color = m_players_colors[player_id];
    // restore previous styling of cell that we are moving head from
    m_cells[m_players_heads[player_id]]->RestoreCellStyling(); 
    // move head
    m_players_heads[player_id] = cell;
    // set focus on currently executed cell
    m_cells[cell]->SetCellFocused(player_color);

    if (modified_cell >= 0 && modified_cell < GUI::CELLS_AMOUNT)
    {
        // set modified styling 
        m_cells[modified_cell]->SetCellModified(player_color);
    }
}


void GUIArena::LoadPlayerCode(int starting_idx, int instructions_amount, int player_id, int offset)
{
    // generate color for a player
    m_GeneratePlayerColor(player_id);
    // we need to check initially if starting_idx and instruction_amount does not exceed arena size
    if (starting_idx >= GUI::CELLS_AMOUNT || starting_idx < 0 ||
         starting_idx + instructions_amount >= GUI::CELLS_AMOUNT || instructions_amount <= 0)
    {
        LOG_ERR("Index of setting players's initial code, is out of bounds, failed to load initial player's code to GUI");
        return;
    }
    // fill instr_amount cells starting from starting index, with player's color
    LOG_DBG("Cells to be colored: {} -> {}", starting_idx, starting_idx + instructions_amount);

    QString player_col = m_players_colors[player_id];
    LOG_DBG("Color for a player: {}", player_col.toStdString());
    for (int i = starting_idx; i < starting_idx + instructions_amount; i++)
    {
        m_cells[i]->SetBackgroundColor(player_col);
    }
    // set record in players heads map
    m_players_heads[player_id] = starting_idx;
    m_cells[starting_idx + offset]->SetCellFocused(player_col);
}


const QString& GUIArena::GetPlayerColorString(int player_id) const
{
    if (m_players_colors.find(player_id) == m_players_colors.end())
    {
        LOG_ERR("Error, requested color of player {} which is out of bounds. Returning white", player_id);
    }
    return m_players_colors.at(player_id);
}


void GUIArena::m_SetCellColor(QLabel* cell, const QString& color)
{
    if (cell == nullptr) {
        LOG_ERR("Cannot change color of cell as it is nullptr");
        return;
    }
}


void GUIArena::m_GeneratePlayerColor(int player_id)
{
    // if color already chosen for a player, reuse it
    if (m_players_colors.find(player_id) != m_players_colors.end())
    {
        LOG_DBG("Color {} already drawn for a player", m_players_colors[player_id].toStdString());    
        return;
    }

    std::random_device r;
    std::mt19937 el(r());
    std::uniform_int_distribution<int> dist(0, GUI::PLAYERS_COLORS.size()-1);
    
    bool can_use = true;
    int color_idx = dist(el);
    // continue with drawing players colors if color has already been chosen for some player
    while (std::find_if(m_players_colors.begin(), m_players_colors.end(), [&](const auto& x) { 
        return x.second == GUI::PLAYERS_COLORS[color_idx];}) != m_players_colors.end())
    {
        // not ideal however should be enough for this purpose
        color_idx = dist(el);
    }
    m_players_colors[player_id] = GUI::PLAYERS_COLORS[color_idx];
    LOG_DBG("Color drawn for a player: {}", m_players_colors[player_id].toStdString());
}