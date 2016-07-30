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
    m_currentFriend = item->text();
    m_currentGroup  = "";
    if (m_userMessages.find(m_currentFriend) == m_userMessages.end())
        m_userMessages[m_currentFriend] = "";
    updateMessages();
}


void MessageHistory::groupSelected(QListWidgetItem *item)
{
    m_currentFriend = "";
    m_currentGroup  = item->text();
    if (m_groupMessages.find(m_currentGroup) == m_groupMessages.end())
        m_groupMessages[m_currentGroup] = "";
    updateMessages();
}


void MessageHistory::sendMessage(QString message)
{
    emit sendUserMessage(m_currentFriend, message);
}

void MessageHistory::recvUserMessage(QString user, QString message)
{
    if (m_userMessages.find(user) == m_userMessages.end())
    {
        m_userMessages[user] = "";
        emit addUser(user);
    }

    m_userMessages[user] += ("<p class='recv-message'>" + message + "</p>");
    //m_messageBuffer.push_back("<p class='recv-message'>" + message + "</p>");
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

    m_userMessages[user] += ("<p class='sent-message'>" + message + "</p>");
    //m_messageBuffer.push_back("<p class='recv-message'>" + message + "</p>");
    if (user == m_currentFriend)
        updateMessages();
}
