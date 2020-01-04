/****************************************************** 
  Arduino library for MCP45HVX1 digital potentiometers
  
  Author: Jonathan Dempsey JDWifWaf@gmail.com
  
  Version: 1.0.1
  License: Apache 2.0
 *******************************************************/

#ifndef _MCP45HVX1_H
#define _MCP45HVX1_H

#include <Arduino.h>
#include <Wire.h>

#define MCPCSPEED 100000     // I2C clock speed

class MCP45HVX1
{
    public:
        
        /* TCON Register Resistor Configuration ............................... */
        typedef struct
        {
            bool R0HW = true;
            bool R0A = true;
            bool R0B = true;
            bool R0W = true;
        }TCON_Register;
 
        /* Setup ............................................................... */
        MCP45HVX1(uint8_t address = 0x3C);

        void begin(TwoWire &inWire = Wire);

        /* Wiper Register ...................................................... */
        uint8_t readWiper();
        void writeWiper(uint8_t wiperValue);
        void incrementWiper(uint8_t incriments = 1);
        void decrementWiper(uint8_t decriments = 1);

        /* TCON Register ....................................................... */
        uint8_t readTCON();
        void writeTCON(TCON_Register *inReg);
        void defaultTCON();

        void inline shutdown()
        {
            write_TCON_R0HW(false);
        }; 
        void inline startup()
        {
            write_TCON_R0HW(true);
        };  
        void inline connectTerminalA()
        {
            write_TCON_R0A(true);
        }; 
        void inline disconnectTerminalA()
        {
            write_TCON_R0A(false);
        };  
        void inline connectTerminalB()
        {
            write_TCON_R0B(true);
        }; 
        void inline disconnectTerminalB()
        {
            write_TCON_R0B(false);
        };  
        void inline connectWiper()
        {
            write_TCON_R0W(true);
        };    
        void inline disconnectWiper()
        {
            write_TCON_R0W(false);
        }; 

    protected:
    private:
         uint8_t _address;

        TwoWire* MCPWire;
        TCON_Register TCON_lib_reg;

        void write_TCON_Register();
        void write_TCON_R0HW(bool state);
        void write_TCON_R0A(bool state);
        void write_TCON_R0W(bool state);
        void write_TCON_R0B(bool state);
};

#endif