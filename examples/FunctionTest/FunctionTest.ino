#include <Arduino.h>
#include "MCP45HVX1.h"

MCP45HVX1 digiPot(0x3C);

void setup()
{  
  Serial.begin(9600);

  digiPot.begin();  

  Serial.println("....... Functionality Test Begin ..........");
  /* Wiper ........................... */
  digiPot.writeWiper(127);                 // Baseline Establish

  Serial.println("\n----- Wiper Register ----");
  Serial.print("readWiper: ");
  Serial.println(digiPot.readWiper());

  Serial.print("writeWiper: ");
  digiPot.writeWiper(200);
  Serial.println(digiPot.readWiper());
  
  Serial.print("incrementWiper: ");
  digiPot.incrementWiper();
  Serial.println(digiPot.readWiper());

  Serial.print("incrementWiper by 2: ");
  digiPot.incrementWiper(2);
  Serial.println(digiPot.readWiper());

  Serial.print("decrementWiper: ");
  digiPot.decrementWiper();
  Serial.println(digiPot.readWiper());

  Serial.print("decrementWiper by 2: ");
  digiPot.decrementWiper(2);
  Serial.println(digiPot.readWiper());

  /* TCON .......................... */
  Serial.println("\n----- TCON Register ----");
  digiPot.disconnectTerminalA();
  Serial.print("disconnectTerminalA: ");
  Serial.println(digiPot.readTCON());
  digiPot.connectTerminalA();
  
  digiPot.disconnectTerminalB();
  Serial.print("disconnectTerminalB: ");
  Serial.println(digiPot.readTCON());
  digiPot.connectTerminalB();

  digiPot.disconnectWiper();
  Serial.print("disconnectWiper: ");
  Serial.println(digiPot.readTCON());
  digiPot.connectWiper();

  digiPot.shutdown();
  Serial.print("shutdown: ");
  Serial.println(digiPot.readTCON());
  digiPot.startup();

  digiPot.startup();
  Serial.print("startup: ");
  Serial.println(digiPot.readTCON());
  digiPot.startup();

  digiPot.defaultTCON();
  Serial.print("default: ");
  Serial.println(digiPot.readTCON());

  Serial.println("\n........ Functionality Test End ...........");
}

void loop()
{
  while(1==1);
} 

