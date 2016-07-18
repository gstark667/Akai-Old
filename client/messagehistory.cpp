#include "messagehistory.h"


void MessageHistory::updateMessages()
{
    QString html = "<html><head><style>p.sent-message { width: 100%; text-align: right; } p.recv-message { width: 100%; text-align: left; }</style></head><body>";
    html += m_userMessages[m_currentUser];
    //for (std::vector<QString>::iterator it = m_messageBuffer.begin(); it != m_messageBuffer.end(); ++it)
    //    html += *it;
    html += "</body>";
    setHtml(html);
}


void MessageHistory::changeUser(QListWidgetItem *user)
{
    m_currentUser = user->text();
    if (m_userMessages.find(m_currentUser) == m_userMessages.end())
        m_userMessages[m_currentUser] = "";
    updateMessages();
}


void MessageHistory::sendMessage(QString message)
{
    if (m_currentUser == "")
        return;

    m_userMessages[m_currentUser] += ("<p class='sent-message'>" + message + "</p>");
    emit sendUserMessage(m_currentUser, message);
    updateMessages();
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
    if (user == m_currentUser)
        updateMessages();
}
