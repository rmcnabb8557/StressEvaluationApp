#include "console.h"

Console::Console(QWidget *parent) :
    QPlainTextEdit(parent)
{
    document()->setMaximumBlockCount(100);
//    QPalette p = palette();
//    p.setColor(QPalette::Base, Qt::black);
//    p.setColor(QPalette::Text, Qt::green);
//    setPalette(p);
}

void Console::writeLine(const QByteArray &data)
{
    insertPlainText(data);
    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}

void Console::setLocalEchoEnabled(bool set)
{
    m_localEchoEnabled = set;
}

void Console::keyPressEvent(QKeyEvent *e)
{
    QTextBlock tb;
    QString command;
    switch (e->key()) {
    //case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    case Qt::Key_Return:
        tb = document()->findBlockByLineNumber(document()->lineCount()-1); // The last line.
        command = tb.text();
        emit(outgoingCommand(command));
    default:
        if (m_localEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
    }
}

void Console::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

//void Console::mouseDoubleClickEvent(QMouseEvent *e)
//{
//    Q_UNUSED(e)
//}

//void Console::contextMenuEvent(QContextMenuEvent *e)
//{
//    Q_UNUSED(e)
//}
