#include "parser.h"

Parser::Parser() : QObject(parent)
{
    serial = new SerialInterface();
}

Parser::Parser(Log* new_log) : QObject(parent)
{
    serial = new SerialInterface();
    log = new_log;
}


Parser::~Parser()
{
    delete serial;
}

void Parser::setSerialInterface(QString serial_port_name)
{
    serial->openSerialPort(serial_port_name);
    connect(serial, SIGNAL(incomingMessageData(QByteArray)), this, SLOT(processIncomingMessage(QByteArray)));
}

void Parser::setConsole(Console* new_console, bool isDebug)
{
    console = new_console;
    if(isDebug){
        console->setReadOnly(false);
        connect(console, SIGNAL(outgoingCommand(QString)),this,SLOT(writeMessage(QString)));
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
           break;
        case VER_MESSAGE:
        case TEST_DATA_MESSAGE:
        default:
            break;
    }

}

void Parser::writeMessage(QString cmd)
{
    // iterate through command list to find cmd header
    QByteArray msg;
    int i = 0;
    while(commands[i].name != "")
    {
        if(commands[i].name == cmd){ // reminder to do a check of the integrity of the data
            msg = commands[i].execute();
            serial->writeMessage(msg);
            break;
        }
        i++;
    }
}
