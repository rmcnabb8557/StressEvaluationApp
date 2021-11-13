#include "serial_interface.h"

Serial_Interface::Serial_Interface(QObject *parent) : QObject(parent)
{

}

Serial_Interface::ReadData()
{
    quint8 header;
    const QByteArray data = serial_port->readAll();
    QTextStream textData(&data, QIODevice::ReadOnly);
    textData >> header;
    int i = 0;
    while(commands[i].name != "")
    {
        if(commands[i].name == header){ // reminder to do a check of the integrity of the data
            *commands[i].execute();
            return;
        }
        i++;
    }
}
