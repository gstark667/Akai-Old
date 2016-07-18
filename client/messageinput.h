#include <QtGui/QKeyEvent>
#include <QtWidgets/QLineEdit>


class MessageInput: public QLineEdit
{
    Q_OBJECT

private:
    bool m_shiftPressed;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public:
    MessageInput(QWidget *parent): QLineEdit(parent), m_shiftPressed(false) {};

signals:
    void sendMessage(QString message);
};
