#ifndef H_AUDIO
#define H_AUDIO

#include <QtCore/QObject>
#include <QtCore/QBuffer>
#include <QtCore/QIODevice>
#include <QtCore/QThread>
#include <QtNetwork/QUdpSocket>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudioOutput>


class Audio: public QObject
{
    Q_OBJECT

private:
    QAudioFormat *m_format;
    QUdpSocket   *m_sock;

    QAudioInput  *m_input;
    QIODevice    *m_inputDevice;

    QAudioOutput *m_output;
    QIODevice    *m_outputDevice;
    QByteArray    m_buffer;

    QHostAddress  m_peerAddress;
    quint16       m_peerPort;

    bool          m_isListen;

public:

    Audio(QObject *parent);
    ~Audio();

    void init(QHostAddress peerAddress, quint16 peerPort);
    void start();
    void stop();

    quint16 getPort();

private slots:
    void readDatagrams();
    void writeDatagrams();

public slots:
    void startListen(QString name);
    void startCall(QHostAddress peerAddress, quint16 peerPort);
    void stopCall();

signals:
    void callFriend(QString name, quint16 port);
};

#endif
