#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QScrollBar>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPlainTextEdit>
#include <QTextBlock>
#include <logger.h>

class Console : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);

signals:
    void outgoingCommand(QString);

public slots:
    void writeLine(QString);

public:
    void setLocalEchoEnabled(bool set);
    void setLog(Logger*);

    Logger* log;

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    //void mouseDoubleClickEvent(QMouseEvent *e) override;

private:
    bool m_localEchoEnabled = true;
};

#endif // CONSOLE_H
