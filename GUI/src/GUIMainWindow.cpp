#include "GUIMainWindow.h"


GUIMainWindow::GUIMainWindow(int width, int height, GUILogicProxy& logic_proxy, QWidget* parent):  m_logic_proxy(logic_proxy), QMainWindow(parent) 
{    
    setWindowTitle("Core Wars");
    setFixedSize(width, height);

    // set batlle field
    m_arena = new GUIArena(80, 100, this);
    setCentralWidget(m_arena);
    // set GUIToolBar
    m_toolBar = new GUIToolBar("Options");
    addToolBar(m_toolBar);

    //set operational panel
    m_op_panel = new GUIOperationalPanel{this};

    // configure right part of the main window for operational panel
    QDockWidget *dockWidget = new QDockWidget(this);
    dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockWidget->setWidget(m_op_panel);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);
    // set background color and font of main window
    SetColor(this, QColorConstants::DarkGray);
    SetTextColor(this);

    // connect main window to proxy, connect child widet to main game logic
    m_ConnectProxy();
}


void GUIMainWindow::m_ConnectProxy()
{
    m_ConnectArena();
    m_ConnectButtons();
}


void GUIMainWindow::m_ConnectArena()
{
    if (m_arena == nullptr)
    {
        LOG_ERR("Tool bar pointer is invalid, failed to set callbacks for game engine");
        return;
    }
    LOG_WRN("Event from game logic received");
    connect(m_arena, &GUIArena::SignalRequestInstructionData, &m_logic_proxy, &GUILogicProxy::SlotInstructionData);
    // we connect main window, but functions are then passed to GUIArena
    // connect(&m_logic_proxy, &GUILogicProxy::SignalPlayerLoad, m_arena, &GUIArena::SlotPlayerLoaded);
    connect(&m_logic_proxy, &GUILogicProxy::SignalPlayerLoad, this, &GUIMainWindow::SlotPlayerLoaded);
    // connect signals responsible for player's movement
    connect(&m_logic_proxy, &GUILogicProxy::SignalPlayerMove, this, &GUIMainWindow::SlotPlayerMove);
    // connect signals responsible for launching instruction info dialog
    connect(&m_logic_proxy, &GUILogicProxy::SignalInstructionData, this, &GUIMainWindow::SlotLaunchInstructionDialog);
    // connect changing counter 
    connect(&m_logic_proxy, &GUILogicProxy::SignalChangeCounter, this, &GUIMainWindow::SlotChangeCounter); 
}

void GUIMainWindow::m_ConnectButtons()
{
    if (m_toolBar == nullptr)
    {
        LOG_ERR("Tool bar pointer is invalid, failed to set callbacks for game engine");
        return;
    }
    // connect load button
    QPushButton* temp = m_toolBar->GetLoadButton();
    if (temp == nullptr)
    {
        LOG_ERR("Load button pointer is invalid, failed to set callback");
        return;
    }
    // we should connect main window to signal from button, retrieve programs path and then pass signal to logic
    connect(temp, &QPushButton::pressed, this, &GUIMainWindow::SlotLoadPlayers);
    connect(this, &GUIMainWindow::SignalLoadPlayers, &m_logic_proxy, &GUILogicProxy::SlotLoadPlayers);
    // connect pause button
    temp = m_toolBar->GetPauseButton();
    if (temp == nullptr)
    {
        LOG_ERR("Pause button pointer is invalid, failed to set callback");
        return;
    }
    connect(temp, &QPushButton::pressed, &m_logic_proxy, &GUILogicProxy::SlotPauseGame);
    // connect play button
    temp = m_toolBar->GetPlayButton();
    if (temp == nullptr)
    {
        LOG_ERR("Play button pointer is invalid, failed to set callback");
        return;
    }
    connect(temp, &QPushButton::pressed, &m_logic_proxy, &GUILogicProxy::SlotStartGame);
    // connect restart button
    temp = m_toolBar->GetRestartButton();
    if (temp == nullptr)
    {
        LOG_ERR("Restart button pointer is invalid, failed to set callback");
        return;
    }
    connect(temp, &QPushButton::pressed, &m_logic_proxy, &GUILogicProxy::SlotRestartGame);
    // restart button should be also connected to Arena
    connect(temp, &QPushButton::pressed, this, &GUIMainWindow::SlotRestartGame);
    // speed up button
    temp = m_toolBar->GetSpeedButtonButton();
    if (temp == nullptr)
    {
        LOG_ERR("Restart button pointer is invalid, failed to set callback");
        return;
    }
    connect(temp, &QPushButton::pressed, &m_logic_proxy, &GUILogicProxy::SlotSpeedUpGame);
    // restart button should be also connected to Arena
    connect(temp, &QPushButton::pressed, this, &GUIMainWindow::SlotSpeedUpGame);

    LOG_DBG("Properly set callback for load button");
}

void GUIMainWindow::SlotChangeCounter(int round_counter)
{
    LOG_PASS("ROUND {}", round_counter);
}


void GUIMainWindow::SlotPlayerLoaded(int starting_idx, int instructions_amount, int player_id, int offset) 
{
    if (m_arena == nullptr) return;
    m_arena->LoadPlayerCode(starting_idx, instructions_amount, player_id, offset);
    // pass color generated for player to stack
    if (m_op_panel == nullptr) return;
    m_op_panel->SetPlayerColor(player_id, m_arena->GetPlayerColorString(player_id));
    LOG_DBG("Player color has been set");
}


void GUIMainWindow::SlotRestartGame()
{
    // clear arena and stacks
    m_arena->ClearArena();
    m_op_panel->ClearStacks();
}

void GUIMainWindow::SlotPlayerMove(int cell, int player_id, int modified_cell, QString instruction) 
{
    if (m_arena == nullptr) return;
    m_arena->MakePlayerMove(cell, player_id, modified_cell);
    if (m_op_panel == nullptr) return;
    m_op_panel->UpdatePlayersStack(player_id, instruction, cell);
}


void GUIMainWindow::SlotLaunchInstructionDialog(QString instruction, int cell_idx)
{
    m_instr_dialog.reset(new GUIInstructionDialog(instruction, cell_idx, this)); // not sure if "this" is needed, to be checked
    m_instr_dialog->show();
}


void GUIMainWindow::SlotLoadPlayers()
{
    // retrieve const ref to vector of player paths TODO
    std::vector<std::string> paths;
    if (!m_op_panel->GetPlayersPaths(paths))
    {
        LOG_ERR("Path for some player has not been chosen");
        return;
    }
    m_arena->ClearArena(); // make sure arena has been cleared before loading new players
    emit SignalLoadPlayers(paths);
}

void GUIMainWindow::SlotSpeedUpGame()
{
    // no implementation for now TODO -> implement
    ;
}