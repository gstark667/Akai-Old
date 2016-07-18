#include "messageinput.h"


void MessageInput::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift)
    {
        m_shiftPressed = true;
        event->accept();
    }
    if (event->key() == Qt::Key_Return && !m_shiftPressed)
    {
        event->accept();
        emit sendMessage(text());
        clear();
    }
    else
    {
        QLineEdit::keyPressEvent(event);
    }
}


void MessageInput::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift)
    {
        m_shiftPressed = false;
        event->accept();
    }
    else
    {
        QLineEdit::keyReleaseEvent(event);
    }
}
