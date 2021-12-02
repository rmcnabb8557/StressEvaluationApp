#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <QObject>
#include <QFile>
#include <QDebug>

class CSVWriter : public QObject
{
    Q_OBJECT
public:
    explicit CSVWriter(QObject *parent = nullptr);
    void setFileName(QString);
    void logEvent(QString);
signals:

private:
    QString m_fileName;
};

#endif // CSVWRITER_H
