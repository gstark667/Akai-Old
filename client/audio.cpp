#include "audio.h"

#include <iostream>


Audio::Audio(): QObject()
{
    m_format = new QAudioFormat();
    m_format->setChannelCount(2);
    m_format->setSampleRate(44100);
    m_format->setSampleSize(16);
    m_format->setCodec("audio/pcm");
    m_format->setByteOrder(QAudioFormat::LittleEndian);
    m_format->setSampleType(QAudioFormat::UnSignedInt);

    m_sock = new QUdpSocket();

    init();

    m_input = new QAudioInput(*m_format);
    m_input->setBufferSize(4096);
    m_inputDevice = m_input->start();

    m_output = new QAudioOutput(*m_format);
    m_output->setBufferSize(4096);
    m_outputDevice = m_output->start();

    connect(m_sock, &QUdpSocket::readyRead, this, &Audio::readDatagrams);
    connect(m_inputDevice, &QIODevice::readyRead, this, &Audio::writeDatagrams);
}


Audio::~Audio()
{
/*
    close();
    m_input->stop();
    m_output->stop();
    delete m_outputBuffer;
    delete m_inputBuffer;
    delete m_input;
    delete m_output;
*/
}


void Audio::init()
{
    m_sock->bind(QHostAddress::LocalHost, 6669);
}


void Audio::readDatagrams()
{
    QByteArray datagram;
    datagram.resize(m_sock->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;

    m_sock->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
    m_buffer.append(datagram);

    while (datagram.size() > 0)
    {
        qint64 i = m_outputDevice->write(datagram.data(), datagram.size());
        datagram.remove(0, i);
    }
}


void Audio::writeDatagrams()
{
    QByteArray datagram = m_inputDevice->read(4096);
    m_sock->writeDatagram(datagram, QHostAddress::LocalHost, 6669);
}

