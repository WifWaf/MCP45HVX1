/****************************************************** 
  Arduino library for MCP45HVX1 digital potentiometers
  
  Author: Jonathan Dempsey JDWifWaf@gmail.com
  
  Version: 1.0.1
  License: Apache 2.0
 *******************************************************/

#include "MCP45HVX1.h"

#define DEBUG 0

/* 7 Bit I2C Operation Components ......................................... */

/* TCON configuration.................. */
#define TCON_R0HW (0x08)  // Shutdown Resistor Force
#define TCON_R0A  (0x04)  // Terminal A Connection 
#define TCON_R0W  (0x02)  // Wiper Connection
#define TCON_R0B  (0x01)  // Terminal B Connection

#define GCALL_TCON          (0x60)
#define GCALL_WIPER         (0x40)
#define GCALL_WIPERUP       (0x42)
#define GCALL_WIPERDWN      (0x44)
#define GCALL_COM_WRITE     (0x02)
#define GCALL_COM_RWRITE    (0x03)
#define GCALL_COM_WIPERINC  (0x42)
#define GCALL_COM_WIPERDEC  (0x44)

#define MEM_WIPER           (0x00)
#define MEM_TCON            (0x40)

#define COM_WRITE           (0x00)
#define COM_READ            (0x0C)
#define COM_WIPERINC        (0x04)
#define COM_WIPERDEC        (0x08)

/* Setup ............................................................... */
MCP45HVX1::MCP45HVX1(uint8_t address) : _address(address) {};
 
void MCP45HVX1::begin(TwoWire &inWire)
{
    MCPWire = &inWire;
    this->MCPWire->begin();
    this->MCPWire->setClock(MCPCSPEED); 
}

/* Wiper Register..........................................................*/
void MCP45HVX1::writeWiper(uint8_t wiperValue)
{
    this->MCPWire->beginTransmission(_address);
    this->MCPWire->write(MEM_WIPER | COM_WRITE);
    this->MCPWire->write(wiperValue);
    this->MCPWire->endTransmission();
} 

uint8_t MCP45HVX1::readWiper()
{
    uint8_t buff = 0;

    this->MCPWire->beginTransmission(_address);
    this->MCPWire->write(MEM_WIPER | COM_READ);
    this->MCPWire->endTransmission(false);

    this->MCPWire->requestFrom(_address, (uint8_t)2);
    if(this->MCPWire->available())
    { 
        buff = this->MCPWire->read();   // First byte is 0x00
        #if DEBUG
        Serial.print("\nRead Wiper MSB:  ");
        Serial.println(buff);
        #endif
        buff = this->MCPWire->read();   // Second byte contains the wiper value
        #if DEBUG
        Serial.print("Read Wiper LSB:  ");
        Serial.println(buff);
        #endif
    }

    return buff;
}

void MCP45HVX1::incrementWiper(uint8_t incriments)
{
    this->MCPWire->beginTransmission(_address);
    for(uint8_t x = 0; x < incriments; x++)
    {
        this->MCPWire->write(MEM_WIPER | COM_WIPERINC);
    }
    this->MCPWire->endTransmission(); 
}

void MCP45HVX1::decrementWiper(uint8_t decriments)
{
    this->MCPWire->beginTransmission(_address);
    for(uint8_t x = 0; x < decriments; x++)
    {
        this->MCPWire->write(MEM_WIPER | COM_WIPERDEC);
    }
    this->MCPWire->endTransmission(); 
} 

/* TCON Register...........................................................*/
uint8_t MCP45HVX1::readTCON()
{
    uint8_t buff = 0;

    this->MCPWire->beginTransmission(_address);
    this->MCPWire->write(MEM_TCON | COM_READ);
    this->MCPWire->endTransmission(false);

    this->MCPWire->requestFrom(_address, (uint8_t)2);
    if(this->MCPWire->available())
    { 
        buff = this->MCPWire->read();   // First byte is always 0x00
         #if DEBUG
        Serial.print("\nRead TCON MSB:  ");
        Serial.println(buff);
        #endif
        buff = this->MCPWire->read();   // Second byte contains the wiper value (for compatability)
        #if DEBUG
        Serial.print("Read TCON LSB:  ");
        Serial.println(buff);
        #endif
    }

    return buff;
}

void MCP45HVX1::defaultTCON()
{
    this->TCON_lib_reg.R0HW = true;
    this->TCON_lib_reg.R0A = true;
    this->TCON_lib_reg.R0B = true;
    this->TCON_lib_reg.R0W = true;

    write_TCON_Register();
}

void MCP45HVX1::writeTCON(TCON_Register *inReg)
{
  memcpy(&this->TCON_lib_reg, inReg, sizeof(this->TCON_lib_reg));
  write_TCON_Register();
}

void MCP45HVX1::write_TCON_R0HW(bool isOn)
{
  this->TCON_lib_reg.R0HW = isOn;
  write_TCON_Register();
}

void MCP45HVX1::write_TCON_R0A(bool isOn)
{
   this->TCON_lib_reg.R0A = isOn;
   write_TCON_Register();
}

void MCP45HVX1::write_TCON_R0W(bool isOn)
{
    this->TCON_lib_reg.R0W = isOn;
    write_TCON_Register();
}

void MCP45HVX1::write_TCON_R0B(bool isOn)
{
    this->TCON_lib_reg.R0B = isOn;
    write_TCON_Register();
}

void MCP45HVX1::write_TCON_Register()
{
    uint8_t buff = 0xFF;

    this->TCON_lib_reg.R0HW ? (buff |= TCON_R0HW) : (buff ^= TCON_R0HW);
    this->TCON_lib_reg.R0A ? (buff |= TCON_R0A) : (buff ^= TCON_R0A);
    this->TCON_lib_reg.R0B ? (buff |= TCON_R0B) : (buff ^= TCON_R0B);
    this->TCON_lib_reg.R0W ? (buff |= TCON_R0W) : (buff ^= TCON_R0W);

    #if DEBUG
    Serial.print("Writing TCON: "); Serial.println(buff);
    #endif

    this->MCPWire->beginTransmission(_address);
    this->MCPWire->write(MEM_TCON | COM_WRITE);
    this->MCPWire->write(buff);
    this->MCPWire->endTransmission();
}

