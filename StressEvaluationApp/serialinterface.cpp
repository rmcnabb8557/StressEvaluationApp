#include "serialinterface.h"

SerialInterface::SerialInterface(QObject *parent) : QObject(parent)
{

}

SerialInterface::~SerialInterface()
{
    delete m_serial_port; // if serial port no exist, do this
}

void SerialInterface::openSerialPort(QString port_name)
{
    m_serial_port = new QSerialPort(port_name);
    connect(m_serial_port, &QSerialPort::errorOccurred,
                this, &SerialInterface::handleError);
    m_serial_port->setBaudRate(115200);
    m_serial_port->open(QIODevice::ReadWrite);
    connect(m_serial_port, SIGNAL(readyRead()), this, SLOT(readData()));
}

void SerialInterface::closeSerialPort()
{
    delete m_serial_port;
}

void SerialInterface::readData()
{
    QByteArray data = m_serial_port->readAll();
    emit(incomingMessageData(data));
}

void SerialInterface::writeMessage(QByteArray msg)
{
    m_serial_port->write(msg);
    m_serial_port->flush();
}

void SerialInterface::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError != QSerialPort::NoError){
        emit(serialError(m_serial_port->errorString()));
    }
}
