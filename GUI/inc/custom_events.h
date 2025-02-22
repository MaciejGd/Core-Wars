#pragma once

#include <QEvent>

class PlayerMoveEvent : public QEvent {
public:
    static const QEvent::Type EventType;
    PlayerMoveEvent(int row, int col); 
    const int GetRow() const { return m_row; }
    const int GetCol() const { return m_col; }
private:
    int m_row;
    int m_col;
};