#include "audio.h"

#include <iostream>


Audio::Audio(QObject *parent): QObject(parent)
{
    m_format = new QAudioFormat();
    m_format->setChannelCount(2);
    m_format->setSampleRate(16000);
    m_format->setSampleSize(16);
    m_format->setCodec("audio/pcm");
    m_format->setByteOrder(QAudioFormat::LittleEndian);
    m_format->setSampleType(QAudioFormat::UnSignedInt);

    m_sock = new QUdpSocket();

    m_input = new QAudioInput(*m_format);
    m_input->setBufferSize(16000);

    m_output = new QAudioOutput(*m_format);
    m_output->setBufferSize(16000);

}


Audio::~Audio()
{
    delete m_format;
    delete m_input;
    delete m_output;
}


void Audio::init(QHostAddress peerAddress, quint16 peerPort)
{
    m_sock->bind(QHostAddress::Broadcast, 0, QUdpSocket::DontShareAddress);
    std::cout << m_sock->localPort() << std::endl;
    m_peerAddress = peerAddress;
    m_peerPort = peerPort;
}

void Audio::start()
{
    m_inputDevice = m_input->start();
    m_outputDevice = m_output->start();

    connect(m_sock, &QUdpSocket::readyRead, this, &Audio::readDatagrams);
    connect(m_inputDevice, &QIODevice::readyRead, this, &Audio::writeDatagrams);
}


void Audio::stop()
{
    disconnect(m_sock, &QUdpSocket::readyRead, this, &Audio::readDatagrams);
    disconnect(m_inputDevice, &QIODevice::readyRead, this, &Audio::writeDatagrams);

    m_sock->close();
    m_outputDevice->close();
    m_inputDevice->close();
}


quint16 Audio::getPort()
{
    return m_sock->localPort();
}


void Audio::readDatagrams()
{
    std::cout << "Reading" << std::endl;
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
    std::cout << "Writing" << std::endl;
    QByteArray datagram = m_inputDevice->read(16000);
    m_sock->writeDatagram(datagram, m_peerAddress, m_peerPort);
}

