#include "logger.h"

Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::setFileName(QString fileName)
{
    QDateTime now;
    m_fileName = fileName;
    QFile file;
    file.setFileName(m_fileName);
    //file->setFileName(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "logging failed.";
        return;
    }
    file.write(QString(" ----- Start of Log " + now.currentDateTime().toString() + " ----- \n").toUtf8().constData());
    file.close();
}

void Logger::logEvent(QString data)
{
    QFile file;
    file.setFileName(m_fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "Logging failed.";
        return;
    }
    file.write(QString("|" + QString::number(m_lineNum++) + "| " + data + "\n").toUtf8().constData());
    file.close();
}

void Logger::logEvent(QByteArray data)
{
    QFile file;
    file.setFileName(m_fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "logging failed.";
        return;
    }
    file.write(QString("|" + QString::number(m_lineNum++) + "| ").toUtf8().constData());
    file.write(data.replace('\n', ' '));
    file.write(QString("\n").toUtf8().constData());
    file.close();
}
