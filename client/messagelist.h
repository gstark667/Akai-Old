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
#include <QtWidgets/QTabWidget>


class FriendMenu: public QMenu
{
    Q_OBJECT

private:
    QString m_friendName;

public:
    FriendMenu(QString friendName, QWidget *parent);

private slots:
    void callSelected();
    void unfriendSelected();

signals:
    void call(QString name);
    void unfriend(QString name);
};


class MessageList: public QTabWidget
{
    Q_OBJECT

private:
    QListWidget *m_friendsList;
    QListWidget *m_groupsList;

public:
    MessageList(QWidget *parent);
    ~MessageList();

    void setupUI();
    void retranslateUI();

public slots:
    void updateFriends(QStringList friends);
    void updateGroups(QStringList groups);
    void nameGroup(QString group, QString name);
    void addFriend(QString);
    void addGroup(QString);
    void showFriendMenu(const QPoint &pos);

signals:
    void getGroupName(QString group);
    void getGroupHistory(QString group);
    void friendSelected(QListWidgetItem *item);
    void groupSelected(QListWidgetItem *item);
    void callFriend(QString name);
    void removeFriend(QString name);
};
