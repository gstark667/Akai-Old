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
private:
    QAudioFormat *m_format;
    QUdpSocket   *m_sock;

    QAudioInput  *m_input;
    QIODevice    *m_inputDevice;

    QAudioOutput *m_output;
    QIODevice    *m_outputDevice;
    QByteArray   m_buffer;

public:
    Audio();
    ~Audio();

    void init();

private slots:
    void readDatagrams();
    void writeDatagrams();
};

#endif
