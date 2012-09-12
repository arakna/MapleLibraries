/*
MCP4131 Digital Potentiometer SPI Library
For LeafLab's Maple IDE (used with Maple microcontroller)
Released to public
Author: BD (Johnnyonthespot)
*/


#ifndef MCP4131_h
#define MCP4131_h

#include "WProgram.h"
#include "HardwareSPI.h"

static HardwareSPI spi(1);

#define MOSI		11
#define MISO		12
#define SCK		13

#define MCP4131_MIN 0 //Tap value Min
#define MCP4131_MAX 128  //Tap value max

class MCP4131
{
public:
	
    MCP4131(int csPin);
	bool initTCON();
	unsigned char readTCON();
	unsigned char readStatus();
	unsigned char  increment();
	unsigned char  decrement();
	unsigned char  setTap(int value);
	void	 setTapFast(byte value);
	unsigned char readTap(); 
	byte Tcon_Reg; //TCON register
	byte Status_Reg; //Status Register
	byte Wiper_Reg; //Wiper Register
	
	
private:
    int _cs;
	void enable();
	void disable();
};

#endif

