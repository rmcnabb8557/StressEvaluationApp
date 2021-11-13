#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H

#include <QObject>
#include <QSerialPort>

#include "SystemMessages.h"

class Serial_Interface : public QObject
{
    Q_OBJECT
public:
    explicit Serial_Interface(QObject *parent = nullptr);
    ~Serial_Interface();

signals:


public slots:
    void OpenSerialPort();
    void CloseSerialPort();
    void ReadData();

private:
    QSerialPort* serial_port;



};

#endif // SERIAL_INTERFACE_H
