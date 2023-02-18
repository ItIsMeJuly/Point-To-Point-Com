#include "MyUART.h"
#include <Arduino.h>

MyUART::MyUART(uint8_t txPin, uint8_t rxPin, uint8_t bits, uint8_t parity, uint8_t stopBits)
{
    this->bits = bits;
    this->parity = parity;
    this->stopBits = stopBits;
    this->rxPin = rxPin;
    this->txPin = txPin;

    pinMode(txPin, OUTPUT);
    digitalWrite(txPin, HIGH);
    pinMode(rxPin, INPUT_PULLUP);
}


void MyUART::println(size_t number)
{
        String text(number);
        
        MyUART::print(text);
        MyUART::print("\n");
}


void MyUART::print(String text)
{
    for (uint8_t i = 0; i < text.length(); i++)
    {
        uint16_t character = text[i];
        uint8_t count = 0;

        // calculate parity
        if (parity == 1)
        {
            count++;
            for (int j = 0; j < bits; j++)
            {
                if (character & (1 << j))
                {
                    count++;
                }
            }
            count = count % 2;
        }

        delayMicroseconds(48);
        digitalWrite(txPin, 0);

        // data bits
        for (int j = 0; j < bits; j++)
        {
            delayMicroseconds(101);
            digitalWrite(txPin, (character >> j) & 0x01);
        }

        // parity bit
        if(parity == 1) // even
        {
            if(count == 0)
            {
                delayMicroseconds(102);
                digitalWrite(txPin, LOW);
            }
            else
            {
                delayMicroseconds(102);
                digitalWrite(txPin, HIGH);
            }
        }

        else if(parity == 2) // odd
        {
            if(count == 0)
            {
                delayMicroseconds(102);
                digitalWrite(txPin, HIGH);
            }
            else
            {
                delayMicroseconds(102);
                digitalWrite(txPin, LOW);
            }
        }

        // stop bits
        for (int j = 0; j < stopBits; j++)
        {
            delayMicroseconds(103);
            digitalWrite(txPin, 1);
        }
    }
}

uint16_t MyUART::read()
{
    return queue.pop();
}


int MyUART::available()
{
    return queue.size();
}


void MyUART::sample()
{
    uint16_t character = 0;

    if(digitalRead(rxPin))
    {
        return;
    }

    uint8_t addedBits = 1;

    // time the middle of the first data bit
    delayMicroseconds(150);


    // safe the data bits and parity
    for (uint16_t i = 0 ;  i < bits + addedBits/*parity*/ ; i++)
    {
        character |= (digitalRead(rxPin) << i);
        delayMicroseconds(102);
    }


    // calculate and check parity
    uint16_t count = 0;
    if (parity != 0)
    {
        for (uint16_t i = 0; i < bits; i++)
        {
            if (((character >> i) & 0x01) == 0x01)
            {
                count++;
            }
        }
        count = count % 2;

        uint16_t parityBit = character & (0x01 << bits);
        parityBit >>= (bits);

        if(parity == 1) // even
        {
            if(parityBit != count)
            {
                return;
            }
        }

        else if(parity == 2) // odd
        {
            if(parityBit == count)
            {
                return;
            }
        }
    }

    character &= ~(1 << (bits));
    // remove the parity from the symbol (MSB)

    // safe character

    queue.push(character);
    // return character;
}
