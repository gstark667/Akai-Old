#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>


// TODO make this a tab widget and make a tab for channels and a tab for chats
class ChannelWidget: public QListWidget
{
    Q_OBJECT

private:
    QListWidgetItem *m_friends;
    QListWidgetItem *m_channels;

public:
    ChannelWidget(QWidget *parent);
    ~ChannelWidget();

public slots:
    void updateFriends(QStringList friends);
    void updateChannels(QStringList channels);
    void addUser(QString);
};
