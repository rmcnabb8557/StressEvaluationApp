#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QVector>
#include "console.h"
#include "serialinterface.h"

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser();
    Parser(Logger*);
    ~Parser();
    void setSerialInterface(QString);
    void setConsole(Console*, bool);


    Logger* log;

signals:
    void dataUpdate(quint64 time, qint16 ecg_diff, quint16 pcg_avg);
    void updateConsole(QString);

public slots:
    void writeMessage(QString);

private slots:
    void processIncomingMessage(QByteArray);
    void writeSerialError(QString);

private:
    SerialInterface* serial;
    Console* console;
};

#endif // PARSER_H
