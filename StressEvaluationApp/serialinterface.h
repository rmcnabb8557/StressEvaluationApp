#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QTextStream>

#include "SystemMessages.h"

class SerialInterface : public QObject
{
    Q_OBJECT
public:
    explicit SerialInterface(QObject *parent = nullptr);
    ~SerialInterface();

signals:
    void incomingMessageData(QByteArray);
    void serialError(QString);

public slots:
    void openSerialPort(QString);
    void closeSerialPort();
    void readData();
    void writeMessage(QByteArray);
    void handleError(QSerialPort::SerialPortError);

private:
    QSerialPort* m_serial_port;



};

#endif // SERIALINTERFACE_H
