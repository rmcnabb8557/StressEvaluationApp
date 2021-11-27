#ifndef SYSTEMMESSAGES_H
#define SYSTEMMESSAGES_H

#include <QByteArray>

typedef QByteArray(*functionPointerType)();
struct commandStruct{
    char const *name;
    quint8 const header;
    functionPointerType execute;
    char const *help;
}; // Abstract Implementation of the Command Object as a C Struct

QByteArray CmdVersionRequest();
QByteArray CmdSDTest();
QByteArray CmdBlinkLED();
QByteArray CmdDataCollect();
QByteArray CmdDataFilter();
QByteArray CmdRun();
QByteArray CmdRunStop();
QByteArray CmdDeepSleep();

const struct commandStruct commands[] = {
    {"ver", 0x61, &CmdVersionRequest,
     "Display Firmware Version"},
    {"sdTest", 2, &CmdSDTest,
     "Runs SD Card test, returns number of errors on completion."},
    {"blinkLed", 3, &CmdBlinkLED,
     "Blinks LED at desired frequency."},
    {"dataCollect", 4, &CmdDataCollect,
     "Collects unfiltered data and transmits data over serial."},
    {"filterTest", 5, &CmdDataFilter,
     "Collects and filters data, and transmits results over serial."},
    {"deepSleep", 6, &CmdDeepSleep,
     "Sets system to deepest sleep available."},
    {"run", 7, &CmdRun,
     "Runs the basic functionality. Exits Debug Idle Mode."}, // need to evaluate in terms of header and such
    {"runstop", 8, &CmdRunStop,
     "Stops system running. Returns to Idle Mode."},
    {"",0, 0,""} // End of Table indicator
}; // Concrete Implementations of several Command Objects

const uint8_t DATA_MESSAGE = 0x11;
const uint8_t VER_MESSAGE = 0x61;
const uint8_t TEST_DATA_MESSAGE = 0xAA;


#endif // SYSTEMMESSAGES_H
