#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QDateTime>
#include <QDebug>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger();
    ~Logger();
    void SetFileName(QString);
    void LogEvent(QString);
    void LogEvent(QByteArray);

signals:

private:
    QFile* file;
    int lineNum = 0;
};

#endif // LOGGER_H
