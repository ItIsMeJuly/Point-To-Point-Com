#ifndef MyUART_H
#define MyUART_H

#include <stdint.h>
#include <Arduino.h>
#include "Queue.h"

#define EVEN_PAR 1
#define ODD_PAR 2

class MyUART
{
private:
    uint8_t bits;
    uint8_t parity;
    uint8_t stopBits;

    Queue queue;

    uint8_t txPin;
    uint8_t rxPin;

public:
    MyUART(uint8_t txPin, uint8_t rxPin, uint8_t bits, uint8_t parity, uint8_t stopBits);

    void print(String text);
    void println(size_t number);

    int available();
    void sample();

    uint16_t read();
};

#endif