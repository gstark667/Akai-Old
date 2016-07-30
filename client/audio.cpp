#include "audio.h"

#include <iostream>


Audio::Audio(): QUdpSocket()
{
    m_format.setChannelCount(1);
    m_format.setSampleRate(4096);
    m_format.setSampleSize(8);
    m_format.setCodec("audio/pcm");
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setSampleType(QAudioFormat::UnSignedInt);

    m_buffer = new QBuffer();

    m_input = new QAudioInput(m_format, this);
    m_input->setBufferSize(1024);
    m_inputDevice = m_input->start();

    m_output = new QAudioOutput(m_format, this);
    m_output->setBufferSize(1024);
    m_outputDevice = m_output->start();

    connect(this, &QUdpSocket::readyRead, this, &Audio::readDatagrams);
    connect(m_inputDevice, &QIODevice::readyRead, this, &Audio::writeDatagrams);
    init();
}


Audio::~Audio()
{
    close();
    m_input->stop();
    m_output->stop();
    delete m_buffer;
    delete m_input;
    delete m_output;
}


void Audio::init()
{
    bind(QHostAddress::LocalHost, 6669);
}


void Audio::readDatagrams()
{
    while (hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        m_outputDevice->write(datagram.data(), datagram.size());
    }
}


void Audio::writeDatagrams()
{
    QByteArray datagram = m_inputDevice->readAll();
    writeDatagram(datagram, QHostAddress("127.0.0.1"), 6669);
}
