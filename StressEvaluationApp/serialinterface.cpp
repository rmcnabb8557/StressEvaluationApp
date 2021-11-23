#include "serialinterface.h"

SerialInterface::SerialInterface(QObject *parent) : QObject(parent)
{

}

SerialInterface::~SerialInterface()
{
    delete serial_port;
}

void SerialInterface::openSerialPort(QString port_name)
{
    serial_port = new QSerialPort(port_name);
    serial_port->setBaudRate(115200);
    serial_port->open(QIODevice::ReadWrite);
    connect(serial_port, SIGNAL(readyRead()), this, SLOT(readData()));
}

void SerialInterface::closeSerialPort()
{

}

void SerialInterface::readData()
{
    QByteArray data = serial_port->readAll();
    emit(incomingMessageData(data));
}

void SerialInterface::writeMessage(QByteArray msg)
{

}
