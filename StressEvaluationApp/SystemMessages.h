#ifndef SYSTEMMESSAGES_H
#define SYSTEMMESSAGES_H

#include <QByteArray>
#include <QDateTime>

typedef QByteArray(*functionPointerType)();
struct commandStruct{
    char const *name;
    quint8 const header;
    functionPointerType execute;
    char const *help;
}; // Abstract Implementation of the Command Object as a C Struct

QByteArray CmdVersionRequest();
QByteArray CmdSync();
QByteArray CmdBlinkLED();
QByteArray CmdDataCollect();
QByteArray CmdSDTest();
QByteArray CmdRun();
QByteArray CmdRunStop();
QByteArray CmdDbgRun();

const struct commandStruct commands[] = {
    {"ver", 'a', &CmdVersionRequest,
     "Display Firmware Version"},
    {"blink", 'c', &CmdBlinkLED,
     "Blinks LED at desired frequency."},
    {"data", 'd', &CmdDataCollect,
     "Collects unfiltered data and transmits data over serial."},
    {"sd", 'b', &CmdSDTest,
     "Collects and filters data, and transmits results over serial."},
    {"drun", 'g', &CmdDbgRun,
     "Sets system to deepest sleep available."},
    {"run", 'f', &CmdRun,
     "Runs the basic functionality. Exits Debug Idle Mode."}, // need to evaluate in terms of header and such
    {"runstop", 'e', &CmdRunStop,
     "Stops system running. Returns to Idle Mode."},
    {"",0, 0,""} // End of Table indicator
}; // Concrete Implementations of several Command Objects

const uint8_t DATA_MESSAGE = 'g';
const uint8_t STRESS_DATA_MESSAGE = 'f';
const uint8_t VER_MESSAGE = 0x61;
const uint8_t TEST_DATA_MESSAGE = 0xAA;


#endif // SYSTEMMESSAGES_H
