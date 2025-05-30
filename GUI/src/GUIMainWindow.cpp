#include "GUIMainWindow.h"
#include "GUIConstants.h"

GUIMainWindow::GUIMainWindow(int width, int height, GUILogicProxy& logic_proxy, QWidget* parent):  m_logic_proxy(logic_proxy), QMainWindow(parent) 
{    
    setWindowTitle("Core Wars");
    //setFixedSize(width, height);

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

void GUIMainWindow::m_ResetCounter()
{
    m_round_cnt = 1;
    // change GUI counter
    m_toolBar->SetCounter(m_round_cnt);
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
    // connect signal responsible for sending info messages from game logic to GUI
    connect(&m_logic_proxy, &GUILogicProxy::SignalShowInfoDialog, this, &GUIMainWindow::SlotShowInfoDialog); 
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
    temp = m_toolBar->GetSpeedUpButton();
    if (temp == nullptr)
    {
        LOG_ERR("SpeedUp button pointer is invalid, failed to set callback");
        return;
    }
    connect(temp, &QPushButton::pressed, &m_logic_proxy, &GUILogicProxy::SlotSpeedUpGame);
    // handle slow down button signal
    temp = m_toolBar->GetSlowDownButton();
    if (temp == nullptr)
    {
        LOG_ERR("SlowDown button pointer is invalid, failed to set callback");
    }
    connect(temp, &QPushButton::pressed, &m_logic_proxy, &GUILogicProxy::SlotSlowDownGame);
}

void GUIMainWindow::SlotPlayerLoaded(int starting_idx, int instructions_amount, int player_id, int offset) 
{
    if (m_arena == nullptr) return;
    m_arena->LoadPlayerCode(starting_idx, instructions_amount, player_id, offset);
    // pass color generated for player to stack
    if (m_op_panel == nullptr) return;
    m_op_panel->SetPlayerColor(player_id, m_arena->GetPlayerColorString(player_id));
    // pass color generated for player to 
    LOG_DBG("Player color has been set");
}


void GUIMainWindow::SlotRestartGame()
{
    m_ResetCounter();
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
    // if player id equal to players amount-1 we are sure that round ended
    if (player_id == GUI::PLAYERS_AMOUNT - 1)
    {
        m_round_cnt++;
        m_toolBar->SetCounter(m_round_cnt);
    }
}


void GUIMainWindow::SlotLaunchInstructionDialog(QString instruction, int cell_idx)
{
    m_instr_dialog.reset(new GUIInstructionDialog(instruction, cell_idx, this)); // not sure if "this" is needed, to be checked
    m_instr_dialog->show();
}


void GUIMainWindow::SlotLoadPlayers()
{
    m_ResetCounter();    
    // retrieve const ref to vector of player paths
    std::vector<std::string> paths;
    if (!m_op_panel->GetPlayersPaths(paths))
    {
        LOG_ERR("Path for some player has not been chosen");
        QString info_msg = "Please choose paths for players before trying to load the code";
        SlotShowInfoDialog(info_msg, true);
        return;
    }
    m_arena->ClearArena(); // make sure arena has been cleared before loading new players
    m_op_panel->ClearStacks();
    emit SignalLoadPlayers(paths);
}

void GUIMainWindow::SlotShowInfoDialog(const QString& msg, bool critical)
{
    QMessageBox msg_box;
    if (critical == true)
    {
        msg_box.setIcon(QMessageBox::Critical);
        msg_box.setWindowTitle("error");
    }
    else {
        msg_box.setIcon(QMessageBox::Information);
        msg_box.setWindowTitle("info");
    }
    msg_box.setText(msg);
    msg_box.setStandardButtons(QMessageBox::Ok);
    msg_box.setDefaultButton(QMessageBox::Ok);
    msg_box.setParent(this);
    msg_box.setWindowModality(Qt::WindowModal);

    // move message box to the center of application
    QRect parentGeometry = this->geometry();
    QPoint centerPos = parentGeometry.center() - msg_box.rect().center()/2;
    msg_box.move(centerPos);

    msg_box.exec();
}