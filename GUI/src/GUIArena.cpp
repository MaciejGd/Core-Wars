#include "GUIArena.h"
#include "GUICustomEvents.cpp"

GUIArena::GUIArena(int rows, int cols, QWidget *parent) : m_rows(rows), m_cols(cols), QWidget(parent) {
    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QLabel *cell = new QLabel;
            cell->setFixedSize(CELL_WIDTH, CELL_WIDTH);  // Set size of each grid cell
            cell->setStyleSheet("background-color: white; border: 1px solid lightGrey;");

            // Enable mouse clicks
            cell->setAutoFillBackground(true);
            cell->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            // store the position of cell
            cell->setProperty("row", i);
            cell->setProperty("col", j);
            cell->installEventFilter(this);
            // add cells to the vector so we can later access it
            m_cells.push_back(cell);

            layout->addWidget(cell, i, j);
        }
    }
    setFixedSize(ARENA_WIDTH, ARENA_HEIGHT);
    setLayout(layout);
}

bool GUIArena::event(QEvent *event) {
    if (event->type() == PlayerMoveEvent::EventType) {
        PlayerMoveEvent* e = reinterpret_cast<PlayerMoveEvent*>(event);
        int row = e->GetRow();
        int col = e->GetCol();
        QLabel* cell = m_cells[row * m_cols + col];
        if (cell != nullptr) {
            cell->setStyleSheet("background-color: red; border: 1px solid lightGrey;");
            return true;
        }
    }
    return false;
}

bool GUIArena::eventFilter(QObject* obj, QEvent* event) {
    // for testing purposes
    if (event->type() == QEvent::MouseButtonPress) {
        QLabel* cell = qobject_cast<QLabel*>(obj);
        if (cell != nullptr) {
            cell->setStyleSheet("background-color: red; border: 1px solid lightGrey;");
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}