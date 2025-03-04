#include "GUIMainWindow.h"

GUIMainWindow::GUIMainWindow(int width, int height, QWidget* parent): QMainWindow(parent) 
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
}