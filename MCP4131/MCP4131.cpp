/*
Maple...
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

unsigned char MCP4131::increment() {
 	enable();
	
	//send in the address and value via SPI:
	//byte ret1 =  0x02 & spi.transfer(0x06); 
	spi.write(0x06);
	byte ret1 = spi.read();
	//Needs bit 1 for error checking, Bit 2 inc

	disable();
	return (ret1 == 0);
}

unsigned char MCP4131::decrement() {
 	enable();
	
	//send in the address and value via SPI:
	//byte ret1 = 0x02 & spi.transfer(0x0A);
	//spi.transfer(0x0A);
	spi.write(0x0A);
	byte ret1 = 0x02 & spi.read();
	//Needs bit 1 for error checking, Bit 3 Dec

	
	disable();
	return (ret1 == 0);
}

unsigned char MCP4131::readTCON() {
 	enable();
	
	// send in the address and value via SPI:
	//byte ret1 = 0x02 & spi.transfer(0x4F); 
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
	//byte ret1 = 0x02 & spi.transfer(0x43); //Address of TCON
	spi.write(0x43);
	byte ret1 = 0x02 & spi.read();
	
	spi.write(0x0F);
	spi.read();
	//byte ret2 = spi.transfer(0x0F); //Set R0* no shutdown *connected 
	disable();
	readTCON();
	return (ret1 == 0); //error checking True if there is some.
}

unsigned char MCP4131::readStatus() {
	enable();
	
	//  send in the address and value via SPI:
	//byte ret1 = 0x02 & spi.transfer(0x5F); //Read Status
	spi.write(0x5F);
	byte ret1 = 0x02 & spi.read();
 
	//Status_Reg = spi.transfer(0xFF);//pull up
	spi.write(0xFF);
	Status_Reg = spi.read();
	
	disable();
	return (ret1 == 0);
}

unsigned char MCP4131::setTap(int value) {
	enable();

	//  send in the address and value via SPI:
	byte h = 0x03 & (value >> 8);
	byte l = 0x00FF & value;
	
	//Serial.print("HIGH: ");
	//Serial.println(h, BIN);
	//Serial.print("LOW: ");
	//Serial.println(l, BIN);
	
	h = h | 0x02; //make sure the error checking bit is high	

	//byte ret1 = 0x02 & spi.transfer(h); //we only want the error bit
	spi.write(h);
	byte ret1 = spi.read();
	spi.write(l);
	spi.read();

	disable();	
	//return (ret1 << 8) | ret2;
	readTap();
	return (ret1 == 0);
}

void MCP4131::setTapFast(byte value) {
	enable();

	 
		

	spi.write(0x00);
	spi.read();
	spi.write(value);
	spi.read();
	// byte ret2 = SPI.transfer(l);

	disable();	
}

unsigned char MCP4131::readTap()
{
	enable();
	//byte ret1 = 0x02 & spi.transfer(0x0F); //Read Wiper 0, check error
	spi.write(0x0F);
	byte ret1 = spi.read();
 
	//Wiper_Reg = spi.transfer(0xFF); //pull up, value stored in wiper register
	spi.write(0xFF);
	Wiper_Reg = spi.read();
	
	disable();

	return (ret1 == 0);
}

