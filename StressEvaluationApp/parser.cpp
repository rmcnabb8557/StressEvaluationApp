#include "parser.h"

Parser::Parser()
{
    serial = new SerialInterface();
}

Parser::Parser(Logger* new_log)
{
    serial = new SerialInterface();
    //connect(serial, SIGNAL(serialError(QString)), this, SLOT());
    log = new_log;
    log->logEvent(QString("Parser Object Created"));
}


Parser::~Parser()
{
    delete serial;
}

void Parser::setSerialInterface(QString serial_port_name)
{
    serial->openSerialPort(serial_port_name);
    log->logEvent(QString("Serial Port ") + serial_port_name + QString(" Opened"));
    connect(serial, SIGNAL(incomingMessageData(QByteArray)), this, SLOT(processIncomingMessage(QByteArray)));
}

void Parser::setConsole(Console* new_console, bool isDebug)
{
    console = new_console;
    if(isDebug){
        console->setReadOnly(false);
        connect(console, SIGNAL(outgoingCommand(QString)),this,SLOT(writeMessage(QString)));
        connect(this, SIGNAL(updateConsole(QString)), console, SLOT(writeLine(QString)));
        connect(serial, SIGNAL(serialError(QString)), console, SLOT(writeLine(QString)));
        connect(serial, SIGNAL(serialError(QString)), this, SLOT(writeSerialError(QString)));
        log->logEvent(QString("Debug Console Opened"));
    }
    else{
        console->setReadOnly(true);
        connect(this, SIGNAL(updateConsole(QString)), console, SLOT(writeLine(QString)));
        connect(serial, SIGNAL(serialError(QString)), console, SLOT(writeLine(QString)));
        connect(serial, SIGNAL(serialError(QString)), this, SLOT(writeSerialError(QString)));
        log->logEvent(QString("Debug Console Opened"));
    }
}

//private slots:
void Parser::processIncomingMessage(QByteArray data)
{
    uint8_t* dataPtr = (uint8_t*)data.data();
    int data_size = data.size();
    static quint64 time = 0;
    qint16 ecg_diff;
    qint16 pcg;
    char ver_major, ver_minor, ver_debug;
    QString consoleMessage;
    log->logEvent(QString("Message recieved. Message type: ") + QString::number(dataPtr[0]));
    int i = 0;
    while(i < data_size){
        switch(dataPtr[i])
        {
            case DATA_MESSAGE:
                time++;
                ecg_diff = qint16(dataPtr[2+i] << 8 | dataPtr[1+i]);
                pcg = quint16(dataPtr[4+i] << 8 | dataPtr[3+i]);
                //pcg2 = quint16(dataPtr[13] << 8 | dataPtr[14]);
                i += 6;
                emit(dataUpdate(time,ecg_diff,pcg));
                break;
            case VER_MESSAGE:
                ver_major = dataPtr[1];
                ver_minor = dataPtr[2];
                ver_debug = dataPtr[3];
                consoleMessage = QString("Version is ") + QString(ver_major) + QString(".") + QString(ver_minor) + QString(".") + QString(ver_debug) + QString("\n");
                i += 4;
                emit(updateConsole(consoleMessage));
                break;
            case TEST_DATA_MESSAGE:
            default:
                emit(updateConsole(QString(data)));
                i++;
                break;
        }
    }

}

void Parser::writeMessage(QString cmd)
{
    // iterate through command list to find cmd header
    QByteArray msg;
    int i = 0;
    log->logEvent(QString("Writing Command ") + cmd);
    while(commands[i].name != "")
    {
        log->logEvent(QString("Command ") + cmd + QString(" searching"));
        if(commands[i].name == cmd){ // reminder to do a check of the integrity of the data
            msg = commands[i].execute();
            serial->writeMessage(msg);
            log->logEvent(QString("Command ") + cmd + QString(" written"));
            log->logEvent(msg);
            return;
        }
        i++;
    }
    log->logEvent(QString("Command ") + cmd + QString(" not found"));
}

void Parser::writeSerialError(QString error){
    log->logEvent(error);
}
