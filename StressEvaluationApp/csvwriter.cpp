#include "csvwriter.h"

CSVWriter::CSVWriter(QObject *parent) : QObject(parent)
{

}

void CSVWriter::setFileName(QString fileName)
{
    m_fileName = fileName;
    QFile file;
    file.setFileName(m_fileName);
    //file->setFileName(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "logging failed.";
        return;
    }
    file.write(QString("t,ecg_raw,ecg_state,ecg_out,pcg_raw,pcg_state,pcg_out,rmssd,avg_latency,hr,stress\n").toUtf8().constData());
    file.close();
}

void CSVWriter::logEvent(QString data)
{
    QFile file;
    file.setFileName(m_fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "Logging failed.";
        return;
    }
    file.write(data.toUtf8() + "\n");
    file.close();
}
