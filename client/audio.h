#ifndef H_AUDIO
#define H_AUDIO

#include <QtCore/QBuffer>
#include <QtCore/QIODevice>
#include <QtNetwork/QUdpSocket>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudioOutput>


class Audio: public QUdpSocket
{
private:
    //TODO we probably want seprate formats for input and output
    QAudioFormat m_format;
    QAudioInput  *m_input;
    QIODevice    *m_inputDevice;
    QAudioOutput *m_output;
    QIODevice    *m_outputDevice;
    QBuffer      *m_buffer;

public:
    Audio();
    ~Audio();

    void init();

private slots:
    void readDatagrams();
    void writeDatagrams();
};

#endif
