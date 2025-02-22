#include "GUICustomEvents.h"

// register event number for custom event
const QEvent::Type PlayerMoveEvent::EventType = static_cast<QEvent::Type>(QEvent::registerEventType());


PlayerMoveEvent::PlayerMoveEvent(int row, int col): m_row(row), m_col(col), QEvent(EventType){}

