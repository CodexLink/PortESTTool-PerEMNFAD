/*
  File Name: IoTMesC_Arduino
  Formalized Name: Iot Multi-Essential Sensing Components for Arduino

  Intended and Flashable To : Arduino MEGA Only
  @ NOTE: We will see how much SRAM will be wasted at the end of this project to ensure validity of using this in Arduino UNO

  Author Name : Janrey "CodexLink" Licas
  Created On: Unknown, Somewhere on Fall 2019
  License: GPL-3.0
*/

#include "IoTMesC_Arduino_CoreDecl.h"

IoTMesC_AVR_DRVR IoTMesC_AVR(0x01c200);

void setup()
{
  IoTMesC_AVR.begin();
}

void loop()
{
  while (1)
  {
    SerialH_Call(println, F("Awaiting for Function Calls."));
    delay(1000);
  }
}