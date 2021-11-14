#include "serial_interface.h"

Serial_Interface::Serial_Interface(QObject *parent) : QObject(parent)
{

}

Serial_Interface::~Serial_Interface()
{

}

void Serial_Interface::OpenSerialPort()
{

}

void Serial_Interface::CloseSerialPort()
{

}

void Serial_Interface::ReadData()
{
    quint8 header;
    QByteArray data = serial_port->readAll();
    header = data[0];
    //crc = data[data.size()-1];
    int i = 0;
    while(commands[i].name != "")
    {
        if(commands[i].header == header){ // reminder to do a check of the integrity of the data
            commands[i].execute(data);
            break;
        }
        i++;
    }
}

void Serial_Interface::WriteData()
{

}
