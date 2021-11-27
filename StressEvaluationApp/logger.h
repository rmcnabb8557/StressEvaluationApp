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
    void setFileName(QString);
    void logEvent(QString);
    void logEvent(QByteArray);

signals:

private:
    QString m_fileName;
    int m_lineNum = 0;
};

#endif // LOGGER_H
