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

    m_input = new QAudioInput(m_format, this);
    m_input->setBufferSize(1024);
    //m_input->start(this);

    m_output = new QAudioOutput(m_format, this);
    m_output->setBufferSize(1024);
    m_output->start(m_input->start());

    connect(this, &QUdpSocket::readyRead, this, &Audio::readDatagrams);
    init();
}


Audio::~Audio()
{
    close();
    m_input->stop();
    m_output->stop();
    delete m_input;
    delete m_output;
}


void Audio::init()
{
    bind(QHostAddress::LocalHost, 6668);
    
}


void Audio::readDatagrams()
{
    while (hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        std::cout << "Read datagram" << std::endl;
    }
}
