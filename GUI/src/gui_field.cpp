#include "gui_field.h"

GuiField::GuiField(int rows, int cols, QWidget *parent) : QWidget(parent) {
    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QLabel *cell = new QLabel;
            cell->setFixedSize(8, 8);  // Set size of each grid cell
            cell->setStyleSheet("background-color: white; border: 1px solid lightGrey;");

            // Enable mouse clicks
            cell->setAutoFillBackground(true);
            cell->setFrameStyle(QFrame::Panel | QFrame::Sunken);

            // Store position for identifying the cell later
            cell->setProperty("row", i);
            cell->setProperty("col", j);

            // Connect label click to color change
            cell->installEventFilter(this);
            
            layout->addWidget(cell, i, j);
        }
    }
    setLayout(layout);
}