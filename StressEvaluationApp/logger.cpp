#include "logger.h"

Logger::Logger()
{
    file = new QFile();
}

Logger::~Logger()
{
    delete file;
}

void Logger::SetFileName(QString fileName)
{
    QDateTime now;
    file->setFileName(fileName);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "logging failed.";
        return;
    }
    file->write(QString(" ----- Start of Log " + now.currentDateTime().toString() + " ----- \n").toUtf8().constData());
    file->close();
}

void Logger::LogEvent(QString data)
{
    if (!file->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "Logging failed.";
        return;
    }
    file->write(QString("|" + QString::number(lineNum++) + "| " + data + "\n").toUtf8().constData());
    file->close();
}

void Logger::LogEvent(QByteArray data)
{
    if (!file->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "logging failed.";
        return;
    }
    file->write(QString("|" + QString::number(lineNum++) + "| ").toUtf8().constData());
    file->write(data.replace('\n', ' '));
    file->write(QString("\n").toUtf8().constData());
    file->close();
}
