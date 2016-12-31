#include "audio.h"

#include <iostream>


AudioWriter::AudioWriter(QIODevice *outputDevice): QThread()
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
            break;
        m_mutex.lock();
        m_data.append(m_buffer);
        m_buffer.clear();
        m_mutex.unlock();
	while (m_data.size() > 0)
	{
	    qint64 i = m_outputDevice->write(m_data.data(), m_data.size());
            if (i == 0)
            {
                msleep(100);
                continue;
            }
	    m_data.remove(0, i);
	}
    }
    std::cout << "Writer finished" << std::endl;
    exit(0);
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
    std::cout << "Stopping writer" << std::endl;
    m_stop = true;
    m_wait.wakeAll();
    wait();
}


AudioSender::AudioSender(QIODevice *inputDevice, QUdpSocket *sock, QList<HostPortPair> peers): QThread()
{
    m_inputDevice = inputDevice;
    m_sock = sock;
    m_peers = peers;
    m_stop = false;
}


void AudioSender::run()
{
    while (true)
    {
        sleep(1);
        if (m_stop)
            break;
        QByteArray buffer = m_inputDevice->readAll();
        if (buffer.size() == 0)
            continue;
        std::cout << "Send: " << buffer.size() << std::endl;
        for (auto peer = m_peers.begin(); peer != m_peers.end(); ++peer)
            m_sock->writeDatagram(buffer, peer->host, peer->port);
    }
    std::cout << "Sender Finished" << std::endl;
    exit(0);
}


void AudioSender::stop()
{
    std::cout << "Stopping Sender" << std::endl;
    m_stop = true;
    wait();
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
    QByteArray datagram;
    QHostAddress senderAddress;
    quint16 senderPort;
    while (m_sock->hasPendingDatagrams())
    {
	datagram.resize(m_sock->pendingDatagramSize());
	m_sock->readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);

        HostPortPair sender = {senderAddress, senderPort};
        if (m_peers.contains(sender))
	    m_writer->addData(datagram);
    }
}


void Audio::startListen(QString name)
{
    std::cout << "STARTING Listen" << std::endl;
    if (m_isListen)
        return; // TODO error message to show that you're already in a call
    m_sock->writeDatagram("Hello World", m_broker, m_port);
    connect(m_sock, &QUdpSocket::readyRead, this, &Audio::readDatagrams);
    std::cout << "Local: " << m_sock->localPort() << " Peer: " << m_sock->peerPort() << std::endl;
    m_isListen = true;
    emit callFriend(name, m_sock->localPort());
}


void Audio::startListenGroup(QString group)
{
    std::cout << "STARTING Listen Group" << std::endl;
    if (m_isListen)
        return; // TODO error message to show that you're already in a call
    m_sock->writeDatagram("Hello World", m_broker, m_port);
    connect(m_sock, &QUdpSocket::readyRead, this, &Audio::readDatagrams);
    std::cout << "Local: " << m_sock->localPort() << " Peer: " << m_sock->peerPort() << std::endl;
    m_isListen = true;
    emit callGroup(group, m_sock->localPort());
}


void Audio::startCall(QHostAddress peerAddress, quint16 peerPort)
{
    std::cout << "STARTING Call" << std::endl;

    peerAddress = QHostAddress("127.0.0.1"); //I use this for testing with 2 clients on one box
    HostPortPair peer = {peerAddress, peerPort};
    m_peers.append(peer);

    m_inputDevice = m_input->start();
    m_outputDevice = m_output->start();
    m_writer = new AudioWriter(m_outputDevice);
    m_writer->start();

    m_sender = new AudioSender(m_inputDevice, m_sock, m_peers);
    m_sender->start();
}


void Audio::stopCall()
{
    m_peers.clear();
    if (m_isListen)
    {
        disconnect(m_sock, &QUdpSocket::readyRead, this, &Audio::readDatagrams);
        m_sock->close();
        m_isListen = false;
    }

    if (m_outputDevice)
    {
        m_writer->stop();
        delete m_writer;
        m_writer = nullptr;

        m_outputDevice->close();
        m_outputDevice = nullptr;
    }

    if (m_inputDevice)
    {
        m_sender->stop();
        delete m_sender;
        m_sender = nullptr;

        m_inputDevice->close();
        m_inputDevice = nullptr;
    }
}

