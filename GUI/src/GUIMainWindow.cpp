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

    // connect main window to proxy, connect child widget to main game logic
    m_ConnectProxy();
}

bool GUIMainWindow::MakePlayerMove(int cell, int player_id)
{
    return m_arena->MakePlayerMove(cell, player_id);
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
    connect(&m_logic_proxy, &GUILogicProxy::SignalPlayerLoad, m_arena, &GUIArena::SlotPlayerLoaded);
}

void GUIMainWindow::m_ConnectButtons()
{
    if (m_toolBar == nullptr)
    {
        LOG_ERR("Tool bar pointer is invalid, failed to set callbacks for game engine");
        return;
    }
    // for debug connect one button first
    QPushButton* temp = m_toolBar->GetLoadButton();
    if (temp == nullptr)
    {
        LOG_ERR("Load button pointer is invalid, failed to set callback");
        return;
    }
    connect(temp, &QPushButton::pressed, &m_logic_proxy, &GUILogicProxy::SlotLoadPlayers);
    LOG_DBG("Properly set callback for load button");
}

