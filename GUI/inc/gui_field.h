#pragma once

#include <QtWidgets>
#include <vector>

#define CELL_WIDTH 10
#define ARENA_WIDTH  1000
#define ARENA_HEIGHT 800

class GuiField : public QWidget {
    Q_OBJECT
public:
    GuiField(int rows, int cols, QWidget *parent = nullptr);
    bool event(QEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    int m_rows;
    int m_cols;
    std::vector<QLabel*> m_cells;
};
