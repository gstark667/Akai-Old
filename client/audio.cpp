#include "audio.h"

#include <iostream>


AudioWriter::AudioWriter(QIODevice *outputDevice)
{
    m_outputDevice = outputDevice;
    m_stop = false;
}


void AudioWriter::run()
{
    QMutex mutex;
    while (true)
    {
        mutex.lock();
        m_wait.wait(&mutex);
        mutex.unlock();
        if (m_stop)
            return;
        m_mutex.lock();
        m_data.append(m_buffer);
        m_buffer.clear();
        m_mutex.unlock();
	while (m_data.size() > 0)
	{
	    qint64 i = m_outputDevice->write(m_data.data(), m_data.size());
	    m_data.remove(0, i);
	}
    }
}


void AudioWriter::addData(QByteArray data)
{
    m_mutex.lock();
    m_buffer.append(data);
    m_mutex.unlock();
    m_wait.wakeAll();
}


void AudioWriter::stop()
{
    m_stop = true;
    m_wait.wakeAll();
}


Audio::Audio(QHostAddress broker, quint16 port, QObject *parent): QObject(parent)
{
    m_broker = broker;
    m_port = port;

    m_format = new QAudioFormat();
    m_format->setChannelCount(2);
    m_format->setSampleRate(16000);
    m_format->setSampleSize(16);
    m_format->setCodec("audio/pcm");
    m_format->setByteOrder(QAudioFormat::LittleEndian);
    m_format->setSampleType(QAudioFormat::UnSignedInt);

    m_sock = new QUdpSocket();

    m_input = new QAudioInput(*m_format);
    m_input->setBufferSize(32000);
    m_inputDevice = nullptr;

    m_output = new QAudioOutput(*m_format);
    m_output->setBufferSize(32000);
    m_outputDevice = nullptr;

    m_isListen = false;

}


Audio::~Audio()
{
    delete m_format;
    delete m_input;
    delete m_output;
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

    if (!m_outputDevice)
        return;

    m_writer->addData(datagram);
}


void Audio::writeDatagrams()
{
    std::cout << "Writing to: " << m_peerPort << std::endl;
    QByteArray datagram = m_inputDevice->read(16000);
    if (!m_isListen)
        return;
    m_sock->writeDatagram(datagram, m_peerAddress, m_peerPort);
}


void Audio::startListen(QString name)
{
    std::cout << "STARTING Listen" << std::endl;
    if (m_isListen)
        return; // TODO error message to show that you're already in a call
    m_sock->writeDatagram("Hello World", m_broker, m_port);
    //m_sock->bind(QHostAddress::Broadcast, m_port, QUdpSocket::DontShareAddress);
    connect(m_sock, &QUdpSocket::readyRead, this, &Audio::readDatagrams);
    std::cout << "Local: " << m_sock->localPort() << " Peer: " << m_sock->peerPort() << std::endl;
    m_isListen = true;
    emit callFriend(name, m_sock->localPort());
}


void Audio::startCall(QHostAddress peerAddress, quint16 peerPort)
{
    std::cout << "STARTING Call" << std::endl;
    m_peerAddress = peerAddress;
    //m_peerAddress = QHostAddress("127.0.0.1"); I use this for testing with 2 clients on one box
    m_peerPort = peerPort;

    m_inputDevice = m_input->start();
    m_outputDevice = m_output->start();
    m_writer = new AudioWriter(m_outputDevice);
    m_writer->start();

    connect(m_sock, &QUdpSocket::readyRead, this, &Audio::readDatagrams);
    connect(m_inputDevice, &QIODevice::readyRead, this, &Audio::writeDatagrams);
}


void Audio::stopCall()
{
    if (m_isListen)
    {
        disconnect(m_sock, &QUdpSocket::readyRead, this, &Audio::readDatagrams);
        m_sock->close();
        m_isListen = false;
    }

    if (m_outputDevice)
    {
        m_outputDevice->close();
        m_outputDevice = nullptr;
    }

    if (m_inputDevice)
    {
        disconnect(m_inputDevice, &QIODevice::readyRead, this, &Audio::writeDatagrams);
        m_writer->stop();
        delete m_writer;
        m_writer = nullptr;
        m_inputDevice->close();
        m_inputDevice = nullptr;
    }
}
