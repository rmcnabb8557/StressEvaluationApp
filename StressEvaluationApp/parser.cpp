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

    }
    // connect signals and slots
}

//public slots:
void Parser::processUpdatedTextEdit(QString string)
{

}

//private slots:
void Parser::processIncomingMessage(QByteArray data)
{
    uint8_t* dataPtr = (uint8_t*)data.data();
    time_t time;
    qint16 ecg_diff;
    quint16 pcg1;
    quint16 pcg2;
    char ver_major, ver_minor;
    QString consoleMessage;
    log->logEvent(QString("Message recieved. Message type: ") + QString::number(dataPtr[0]));
    switch(dataPtr[0])
    {
        case DATA_MESSAGE:
            time = time_t(dataPtr[4] | (dataPtr[3] << 8) | (dataPtr[2] << 16)
                               | (dataPtr[1] << 24));
            ecg_diff = qint16(dataPtr[9] << 8 | dataPtr[10]);
            pcg1 = quint16(dataPtr[11] << 8 | dataPtr[12]);
            pcg2 = quint16(dataPtr[13] << 8 | dataPtr[14]);
            v_time.append(double(time));
            v_ecg_diff.append(double(ecg_diff));
            v_pcg_avg.append(double((pcg1 + pcg2)/2));
            if(v_time.size() > 6000)
            {
               v_time.removeFirst();
               v_ecg_diff.removeFirst();
               v_pcg_avg.removeFirst();
            }
            //emit some shit
            break;
        case VER_MESSAGE:
            ver_major = dataPtr[1];
            ver_minor = dataPtr[2];
            consoleMessage = QString("Version is ") + QString(ver_major) + QString(":") + QString(ver_minor) + QString("\n");
            emit(updateConsole(consoleMessage));
            break;
        case TEST_DATA_MESSAGE:
        default:
            emit(updateConsole(QString(data)));
            break;
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
            return;
        }
        i++;
    }
    log->logEvent(QString("Command ") + cmd + QString(" not found"));
}

void Parser::writeSerialError(QString error){
    log->logEvent(error);
}
