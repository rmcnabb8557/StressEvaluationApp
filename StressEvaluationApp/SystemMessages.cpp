#include <SystemMessages.h>

QByteArray CmdVersionRequest(){
    QByteArray qb;
    qb.append(0x61);
    return qb;
}

QByteArray CmdSync(){
    QByteArray qb;
    qb.append(0x65);
    QDateTime now;
    time_t rtcData = now.currentSecsSinceEpoch();
    char *rtcData_ptr = (char*)&rtcData;
    //for(int i = 4; i > 0; i++){
    qb.append(QByteArray::fromRawData(rtcData_ptr,4));
    //}
    return qb;
}

QByteArray CmdBlinkLED(){

}

QByteArray CmdDataCollect(){

}

QByteArray CmdDataFilter(){

}

QByteArray CmdRun(){
    QByteArray qb;
    qb.append(0x71);
    QDateTime now;
    time_t rtcData = now.currentSecsSinceEpoch();
    char *rtcData_ptr = (char*)&rtcData;
    //for(int i = 4; i > 0; i++){
    qb.append(QByteArray::fromRawData(rtcData_ptr,4));
    //}
    return qb;
}

QByteArray CmdRunStop(){

}

QByteArray CmdDbgRun(){
    QByteArray qb;
    qb.append(0x41);
    QDateTime now;
    time_t rtcData = now.currentSecsSinceEpoch();
    char *rtcData_ptr = (char*)&rtcData;
    //for(int i = 4; i > 0; i++){
    qb.append(QByteArray::fromRawData(rtcData_ptr,4));
    qb.append(0x71);
    //}
    return qb;
}
