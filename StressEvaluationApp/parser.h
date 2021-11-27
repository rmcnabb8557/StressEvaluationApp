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

    QVector<double> v_time;
    QVector<double> v_ecg_diff;
    QVector<double> v_pcg_avg;
    QVector<double> v_stress;
    Logger* log;

signals:
    void dataUpdate(QVector<double>& time, QVector<double>& ecg_diff, QVector<double>& pcg_avg, QVector<double>& stress);
    void updateConsole(QString);

public slots:
    void processUpdatedTextEdit(QString);
    void writeMessage(QString);

private slots:
    void processIncomingMessage(QByteArray);
    void writeSerialError(QString);

private:
    SerialInterface* serial;
    Console* console;
};

#endif // PARSER_H
