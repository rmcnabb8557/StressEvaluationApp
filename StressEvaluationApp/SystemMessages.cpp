#include <SystemMessages.h>

QByteArray CmdVersionRequest(){
    QByteArray qb;
    qb.append(0x61);
    qb.append(0x61); // adjust this for the crc value
    return qb;
}

QByteArray CmdSDTest(){

}

QByteArray CmdBlinkLED(){

}

QByteArray CmdDataCollect(){

}

QByteArray CmdDataFilter(){

}

QByteArray CmdRun(){

}

QByteArray CmdRunStop(){

}

QByteArray CmdDeepSleep(){

}
