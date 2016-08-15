#ifndef H_AUDIO
#define H_AUDIO

#include <QtCore/QWaitCondition>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QIODevice>
#include <QtCore/QObject>
#include <QtCore/QBuffer>
#include <QtCore/QIODevice>
#include <QtCore/QThread>
#include <QtNetwork/QUdpSocket>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudioOutput>


class AudioWriter: public QThread
{
private:
    QIODevice     *m_outputDevice;
    QWaitCondition m_wait;
    QMutex         m_mutex;
    QByteArray     m_buffer;
    QByteArray     m_data;

    bool           m_stop;

public:
    AudioWriter(QIODevice *outputDevice);

    void run();
    void addData(QByteArray data);
    void stop();
};


class AudioSender: public QThread
{
private:
    QIODevice     *m_inputDevice;
    QUdpSocket    *m_sock;
    QHostAddress   m_peerAddress;
    quint16        m_peerPort;

    bool           m_stop;

public:
    AudioSender(QIODevice *inputDevice, QUdpSocket *sock, QHostAddress peerAddress, quint16 peerPort);

    void run();
    void stop();
};


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
    AudioWriter  *m_writer;
    AudioSender  *m_sender;

    QHostAddress  m_peerAddress;
    quint16       m_peerPort;

    bool          m_isListen;
    QHostAddress  m_broker;
    quint16       m_port;

public:

    Audio(QHostAddress broker, quint16 port, QObject *parent);
    ~Audio();

    void init(QHostAddress peerAddress, quint16 peerPort);
    void start();
    void stop();

    quint16 getPort();

private slots:
    void readDatagrams();

public slots:
    void startListen(QString name);
    void startCall(QHostAddress peerAddress, quint16 peerPort);
    void stopCall();

signals:
    void callFriend(QString name, quint16 port);
};

#endif
