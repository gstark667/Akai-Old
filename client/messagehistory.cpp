#include "messagehistory.h"

#include <iostream>


void MessageHistory::updateMessages()
{
    QString html = "<html><head><style>p.sent-message { width: 100%; text-align: right; } p.recv-message { width: 100%; text-align: left; }</style></head><body>";
    if (m_currentFriend.size() > 0)
        html += m_userMessages[m_currentFriend];
    else if (m_currentGroup.size() > 0)
        html += m_groupMessages[m_currentGroup];
    html += "</body>";
    setHtml(html);
}


void MessageHistory::friendSelected(QListWidgetItem *item)
{
    std::cout << "Friend Selected" << std::endl;
    m_currentFriend = item->text();
    m_currentGroup  = "";
    if (m_userMessages.find(m_currentFriend) == m_userMessages.end())
        m_userMessages[m_currentFriend] = "";
    updateMessages();
}


void MessageHistory::groupSelected(QListWidgetItem *item)
{
    std::cout << "Group Selected" << std::endl;
    m_currentFriend = "";
    m_currentGroup  = item->data(Qt::UserRole).toString();
    if (m_groupMessages.find(m_currentGroup) == m_groupMessages.end())
        m_groupMessages[m_currentGroup] = "";
    updateMessages();
}


void MessageHistory::sendMessage(QString message)
{
    std::cout << "Current Friend: " << m_currentFriend.toStdString() << std::endl;
    std::cout << "Current Group: " << m_currentGroup.toStdString() << std::endl;
    if (m_currentFriend != "")
        emit sendUserMessage(m_currentFriend, message);
    if (m_currentGroup != "")
        emit sendGroupMessage(m_currentGroup, message);
}


void MessageHistory::recvUserMessage(QString user, QString message)
{
    if (m_userMessages.find(user) == m_userMessages.end())
    {
        m_userMessages[user] = "";
        emit addUser(user);
    }

    m_userMessages[user] += ("<p class='recv-message'>" + message.toHtmlEscaped() + "</p>");
    if (user == m_currentFriend)
        updateMessages();
}


void MessageHistory::sentUserMessage(QString user, QString message)
{
    if (m_userMessages.find(user) == m_userMessages.end())
    {
        m_userMessages[user] = "";
        emit addUser(user);
    }

    m_userMessages[user] += ("<p class='sent-message'>" + message.toHtmlEscaped() + "</p>");
    if (user == m_currentFriend)
        updateMessages();
}


void MessageHistory::recvGroupMessage(QString group, QString user, QString message)
{
    if (m_groupMessages.find(group) == m_groupMessages.end())
        m_groupMessages[group] = "";

    m_groupMessages[group] += ("<p class='recv-message'><bold>" + user + "</bold><br/>" + message.toHtmlEscaped() + "</p>");
    if (group == m_currentGroup)
        updateMessages();
}


void MessageHistory::sentGroupMessage(QString group, QString message)
{
    if (m_groupMessages.find(group) == m_groupMessages.end())
        m_groupMessages[group] = "";

    m_groupMessages[group] += ("<p class='sent-message'>" + message.toHtmlEscaped() + "</p>");
    if (group == m_currentGroup)
        updateMessages();
}

