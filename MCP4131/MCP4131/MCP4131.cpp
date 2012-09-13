/*
MCP4131 Digital Potentiometer SPI Library
For LeafLab's Maple IDE (used with Maple microcontroller)
Released to public
Author: BD (Johnnyonthespot)
*/

#include "MCP4131.h"

MCP4131::MCP4131(int csPin)
{
	//Sets SS/CS pin
	_cs = csPin;
	pinMode(_cs, OUTPUT);
	disable();
	
	//Spi setup and begin
	spi.begin(SPI_2_25MHZ , MSBFIRST, 0);
}

void MCP4131::enable() {
	// take the SS pin low to select the chip:
	digitalWrite(_cs, LOW);
}

void MCP4131::disable() {
	// take the SS pin high to de-select the chip:
	digitalWrite(_cs, HIGH);
}

bool MCP4131::increment() {
 	enable();
	
	//send in the address and value via SPI:
	spi.write(0x06);
	byte ret1 = spi.read();
	//Needs bit 1 for error checking, Bit 2 inc
	disable();
	return (ret1 == 0);
}

bool MCP4131::decrement() {
 	enable();
	
	//send in the address and value via SPI:
	spi.write(0x0A);
	byte ret1 = 0x02 & spi.read();
	//Needs bit 1 for error checking, Bit 3 Dec
	
	disable();
	return (ret1 == 0);
}

bool MCP4131::readTCON() {
 	enable();
	
	// send in the address and value via SPI:
	spi.write(0x4F);
	byte ret1 = 0x02 & spi.read();
	// At memory address 4 we read
	
	//Tcon_Reg = spi.transfer(0xFF); //Pull UP
	spi.write(0xFF);
	Tcon_Reg = spi.read();
	
	disable();
	return (ret1 == 0); //error checking 
}

bool MCP4131::initTCON() { 
	//Turns on Wiper 0, connects the terminals to the resistor network.
	enable();
	
	//  send in the address and value via SPI:
	spi.write(0x43);
	byte ret1 = 0x02 & spi.read();
	
	spi.write(0x0F);
	spi.read();
	
	disable();
	readTCON();
	return (ret1 == 0); //error checking True if there is some.
}

bool MCP4131::readStatus() {
	enable();
	
	//send in the address and value via SPI:
	spi.write(0x5F);
	byte ret1 = 0x02 & spi.read();
 
	//Status_Reg = spi.transfer(0xFF);//pull up
	spi.write(0xFF);
	Status_Reg = spi.read();
	
	disable();
	return (ret1 == 0);
}

bool MCP4131::setTap(int value) {
	enable();

	//  send in the address and value via SPI:
	byte h = 0x03 & (value >> 8);
	byte l = 0x00FF & value;
	
	h = h | 0x02; //make sure the error checking bit is high	

	spi.write(h);
	byte ret1 = spi.read();
	spi.write(l);
	spi.read();

	disable();	

	readTap();
	return (ret1 == 0);
}

void MCP4131::setTapFast(byte value) {
	enable();
	
	spi.write(0x00);
	spi.read();
	spi.write(value);
	spi.read();

	disable();	
}

bool MCP4131::readTap()
{
	enable();

	spi.write(0x0F);
	byte ret1 = spi.read();
 
	//pull up, value stored in wiper register
	spi.write(0xFF);
	Wiper_Reg = spi.read();
	
	disable();

	return (ret1 == 0);
}

