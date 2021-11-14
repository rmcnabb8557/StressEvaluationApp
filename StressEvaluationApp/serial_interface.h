#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QTextStream>

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
    void WriteData();

private:
    QSerialPort* serial_port;



};

#endif // SERIAL_INTERFACE_H
