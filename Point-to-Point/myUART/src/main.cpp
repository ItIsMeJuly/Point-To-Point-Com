#include <Arduino.h>
#include "MyUART.h"

#define MAX_TIMEOUT 0xFFFFFFFFu

MyUART uart(3, 4, 7, EVEN_PAR, 2);
uint16_t command;

void StartMenu()
{
  uart.print("View current Input Levels\n");
  uart.print("- D: Digital Input D8 - D13\n");
  uart.print("- A: Analog Inputs A1 - A5\n");
  uart.print("- C: Clear session\n\n");
}

void setup()
{
  // put your setup code here, to run once:
  StartMenu();
}

void loop()
{
  uart.sample();

  if(uart.available() != 0)
  {
    command = uart.read();

    StartMenu();
  }
  else
  {
    command = 0;
  }

  if ((char)command == 'D')
  {
    uart.print("DI8: ");
    uart.println(digitalRead(8));
    uart.print("DI9: ");
    uart.println(digitalRead(9));
    uart.print("DI10:");
    uart.println(digitalRead(10));
    uart.print("DI11:");
    uart.println(digitalRead(11));
    uart.print("DI12:");
    uart.println(digitalRead(12));
    uart.print("DI13:");
    uart.println(digitalRead(13));
    uart.print("\n");
  }
  else if ((char)command == 'A')
  {
    uart.print("AI0: ");
    uart.println(analogRead(14));
    uart.print("AI1: ");
    uart.println(analogRead(15));
    uart.print("AI2: ");
    uart.println(analogRead(16));
    uart.print("AI3: ");
    uart.println(analogRead(17));
    uart.print("AI4: ");
    uart.println(analogRead(18));
    uart.print("AI5: ");
    uart.println(analogRead(19));
    uart.print("\n");
  }
  else if ((char)command == 'C')
  {
    for (int i = 0; i < 11; i++)
    {
      uart.print("\n");
      uart.print("\n");
    }
  }
}