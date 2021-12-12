#include <SystemMessages.h>

QByteArray CmdVersionRequest(){
    QByteArray qb;
    qb.append('a');
    return qb;
}

QByteArray CmdSync(){
    QByteArray qb;
    qb.append(0x65);
    return qb;
}

QByteArray CmdBlinkLED(){
    QByteArray qb;
    qb.append('c');
    return qb;
}

QByteArray CmdDataCollect(){
    QByteArray qb;
    qb.append('d');
    return qb;
}

QByteArray CmdSDTest(){
    QByteArray qb;
    qb.append('b');
    return qb;
}

QByteArray CmdRun(){
    QByteArray qb;
    qb.append('f');
    return qb;
}

QByteArray CmdRunStop(){
    QByteArray qb;
    qb.append('e');
    return qb;
}

QByteArray CmdDbgRun(){
    QByteArray qb;
    qb.append('g');
    return qb;
}
